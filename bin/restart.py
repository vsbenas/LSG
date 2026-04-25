import sys
import mysql.connector
import os

if len(sys.argv) < 2:
    print("Invalid delay in mins. Use restart.py [0-10] for a delay of 0-10 minutes.")
    exit()

cnx = mysql.connector.connect(user=os.environ['LSG_DB_USER'], password=os.environ['LSG_DB_PASSWORD'], host=os.environ['LSG_DB_HOST'], database=os.environ['LSG_DB_DATABASE'])

delay_mins = int(sys.argv[1])
if delay_mins < 0 or delay_mins > 10:
    print("Invalid delay in mins. Use restart.py [0-10] for a delay of 0-10 minutes.")
    exit()
    
cursor = cnx.cursor()

query = ('Update Config set value=%s where variable="Restart"')

cursor.execute(query, [delay_mins])

cnx.commit()
print("Restart scheduled in {} mins!".format(delay_mins))

cnx.close()