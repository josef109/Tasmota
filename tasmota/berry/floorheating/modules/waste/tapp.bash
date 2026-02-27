#!/bin/bash

# 1. Verzeichnis des Scripts und Ordnernamen ermitteln
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
FOLDER_NAME=$(basename "$SCRIPT_DIR")
TARGET_DIR="$SCRIPT_DIR/bin"

# 2. Prüfen, ob der bin-Ordner existiert
if [ ! -d "$TARGET_DIR" ]; then
    echo "Hinweis: Ordner 'bin' wurde nicht gefunden. Erstelle $TARGET_DIR..."
    mkdir -p "$TARGET_DIR"
fi

# 3. In das Script-Verzeichnis wechseln (sicherstellt, dass die Wildcards greifen)
cd "$SCRIPT_DIR"

# 4. Den Zip-Befehl ausführen
echo "Erstelle Paket: ${FOLDER_NAME}.tapp im bin-Verzeichnis..."
zip -Z store "$TARGET_DIR/${FOLDER_NAME}.tapp" *.be pages.jsonl *.png *.svg
