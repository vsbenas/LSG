import sys
import mysql.connector
import os
import json

if len(sys.argv) < 2:
    exit()

cnx = mysql.connector.connect(user=os.environ['LSG_DB_USER'], password=os.environ['LSG_DB_PASSWORD'], host=os.environ['LSG_DB_HOST'], database=os.environ['LSG_DB_DATABASE'])

if sys.argv[1] == 'load':
    print("Loading bans")
    cursor = cnx.cursor(dictionary=True)

    query = ("SELECT * From Permabans")

    cursor.execute(query)
    res = []
    for row in cursor:
        res.append(row)
    print(res)
    with open('bans.json', 'w') as f:
        json.dump(res, f, indent=4) 
    print(str(len(res)) + " bans loaded and written to bans.json!")

if sys.argv[1] == 'save':
    print("Saving bans")

    with open('bans.json', 'r') as f:
        data = json.load(f)

    print(data)
    
    cursor = cnx.cursor()

    query = ('REPLACE INTO Permabans(address, player, reason, time) VALUES (%s,%s,%s,%s)')

    for row in data:
        print(row)
        cursor.execute(query, (row['address'],row['player'],row['reason'],row['time']))
    
    cnx.commit()
    print(str(len(data)) + " bans stored in DB!")

cnx.close()