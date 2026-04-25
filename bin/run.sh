#!/bin/bash
echo "Populating secrets"
envsubst < mysql.ini | sponge mysql.ini
envsubst < config.json | sponge config.json

echo "Loading bans..."
python3 ./bans.py load

echo "Starting LSG O:MP server"

./omp-server

echo "Saving bans..."

python3 ./bans.py save

echo "Exiting"