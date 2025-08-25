#include <vector>
#include <cmath>
#include <algorithm>

#define TEMP_OFFSET_LP (-6)
#define HUM_OFFSET_LP (82)
#define GAS_RECAL_PERIOD (3600)
#define SLOPE (0.03)
#define DEF_BURN_IN_CYCLES 300

class IAQTracker
{
private:
    int burn_in_cycles;
    float gas_ceil;
    int gas_recal_step;
    int temp_ofs;
    int hum_ofs;
    std::vector<float> gas_cal_data;
    uint32_t crc;

public:
    IAQTracker(int burn_in_cycles = DEF_BURN_IN_CYCLES)
        : burn_in_cycles(burn_in_cycles), gas_ceil(0.0), gas_recal_step(0), temp_ofs(TEMP_OFFSET_LP), hum_ofs(HUM_OFFSET_LP), crc(0xffffffff) {}

    float getTemOfs(void)
    {
        return ((float)temp_ofs) / 10.0;
    }
    float getHumOfs(void)
    {
        return ((float)hum_ofs) / 10.0;
    }
    void setTempOfs(float ofs)
    {
        temp_ofs = int(ofs * 10.0);
    }
    void setHumOfs(float ofs)
    {
        hum_ofs = int(ofs * 10.0);
    }
    // Berechnet die Sättigungswasserdichte der Luft bei gegebener Temperatur (in °C)
    float waterSatDensity(float temp)
    {
        return (6.112 * 100 * std::exp((17.62 * temp) / (243.12 + temp))) / (461.52 * (temp + 273.15));
    }

    uint16_t getIAQ(float temp, float hum, float R_gas)
    {
        float rho_max = waterSatDensity(temp);
        float hum_abs = hum * 10 * rho_max;

        if ((R_gas < 0.1) || (R_gas > 600000.0))
            return 0;
        // Exponentielle Kompensation des Feuchtigkeitseinflusses auf den Widerstand
        float comp_gas = R_gas * std::exp(SLOPE * hum_abs);

        if (burn_in_cycles > 0)
        {
            burn_in_cycles--;
            if (comp_gas > gas_ceil)
            {
                gas_cal_data.clear();
                gas_cal_data.push_back(comp_gas);
                gas_ceil = comp_gas;
            }
            return 50; // Burn-in nicht abgeschlossen
        }
        if (comp_gas > gas_ceil)
        {
            gas_cal_data.push_back(comp_gas);
            if (gas_cal_data.size() > 100)
            {
                gas_cal_data.erase(gas_cal_data.begin());
            }
            gas_ceil = mean(gas_cal_data);
        }

        // Berechnung der Luftqualität
        uint16_t AQ = int(500.0 - std::min(std::pow(comp_gas / gas_ceil, 2), 1.0) * 500.0);

        // Kalibrierung aktualisieren
        gas_recal_step++;
        if (gas_recal_step >= GAS_RECAL_PERIOD)
        {
            gas_recal_step = 0;
            gas_cal_data.push_back(comp_gas);
            gas_cal_data.erase(gas_cal_data.begin());
            gas_ceil = mean(gas_cal_data);
        }

        return AQ;
    }

    void clean(void)
    {
        gas_cal_data.clear();
        burn_in_cycles = DEF_BURN_IN_CYCLES;
        temp_ofs = TEMP_OFFSET_LP;
        hum_ofs = HUM_OFFSET_LP;
        gas_ceil = 0.0;
        gas_recal_step = 0;
        crc = 0xffffffff;
    }

    void saveToBinaryFile(File &file)
    {
        crc = GetCfgCrc32(reinterpret_cast<uint8_t *>(&burn_in_cycles), sizeof(temp_ofs) 
            + sizeof(hum_ofs) + sizeof(gas_ceil) + sizeof(gas_recal_step) + gas_cal_data.size() * sizeof(float));
        file.write(reinterpret_cast<const uint8_t *>(&temp_ofs), sizeof(temp_ofs));
        file.write(reinterpret_cast<const uint8_t *>(&hum_ofs), sizeof(hum_ofs));
        file.write(reinterpret_cast<const uint8_t *>(&burn_in_cycles), sizeof(burn_in_cycles));
        file.write(reinterpret_cast<const uint8_t *>(&gas_ceil), sizeof(gas_ceil));
        file.write(reinterpret_cast<const uint8_t *>(&gas_recal_step), sizeof(gas_recal_step));
        size_t size = gas_cal_data.size();
        file.write(reinterpret_cast<const uint8_t *>(&size), sizeof(size));
        file.write(reinterpret_cast<const uint8_t *>(gas_cal_data.data()), size * sizeof(float));
        file.write(reinterpret_cast<const uint8_t *>(&crc), sizeof(crc));
    }

    bool loadFromBinaryFile(File &file)
    {
        file.read(reinterpret_cast<uint8_t *>(&temp_ofs), sizeof(temp_ofs));
        file.read(reinterpret_cast<uint8_t *>(&hum_ofs), sizeof(hum_ofs));
        file.read(reinterpret_cast<uint8_t *>(&burn_in_cycles), sizeof(burn_in_cycles));
        file.read(reinterpret_cast<uint8_t *>(&gas_ceil), sizeof(gas_ceil));
        file.read(reinterpret_cast<uint8_t *>(&gas_recal_step), sizeof(gas_recal_step));
        size_t size;
        file.read(reinterpret_cast<uint8_t *>(&size), sizeof(size));
        if (size <= 3600)
        {
            gas_cal_data.resize(size);
            file.read(reinterpret_cast<uint8_t *>(gas_cal_data.data()), size * sizeof(float));
            file.read(reinterpret_cast<uint8_t *>(&crc), sizeof(crc));
        }
        else
        {
            clean();
            return false;
        }
        uint32_t c = GetCfgCrc32(reinterpret_cast<uint8_t *>(&burn_in_cycles), sizeof(temp_ofs) 
            + sizeof(hum_ofs) + sizeof(gas_ceil) + sizeof(gas_recal_step) + gas_cal_data.size() * sizeof(float));
        if(c != crc)
        {
            clean();
            return false;
        }
        return true;
    }

private:
    float mean(const std::vector<float> &values)
    {
        float sum = 0.0;
        for (float v : values)
        {
            sum += v;
        }
        return values.empty() ? 0.0 : sum / values.size();
    }
};
