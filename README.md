# Los Santos Gyvenimas

<center>

![logo](https://i.imgur.com/IxNr6XB.png) 

</center>

𥇱𥇹 **Los Santos Gyvenimas** - vienas didžiausių lietuviťkų SA:MP serverių, aktyviai veikęs 2010-2026 metais. 

[LSGyvenimas.lt](http://www.lsgyvenimas.lt)


## Installation instructions


**Prerequisites**: Docker, Git.

 **Clone the repository**:
- `git clone https://github.com/vsbenas/lsg`
- `cd lsg`

**Set up database**:
- If you don't have a MySQL server, follow the instructions under [MySQL quickstart](#mysql-quickstart).
- Rename `.env.example` to `.env`. Fill out the details.
- Create database with name given to `LSG_DB_DATABASE` in `.env`.
- Set up the database using the `deployments/db/init.sql` script. See [DB Seeding](#db-seeding).

**Build and launch**:

- Build the image: `docker build -t lsg .`
- Run the server: `docker run --network host --env-file .env -it --name lsg lsg`



You're done! You can now join the server using `127.0.0.1:7777`.

## Known issues
 - SA:MP MySQL plugin does not connect to MySQL servers requiring SSL. Running a MySQL server locally helps to avoid this problem.
 - Email and SMS sending is disabled because they require outside integrations.
 - Source files must be edited in `windows1257` encoding, otherwise Lithuanian characters will get corrupted. This is prone to happen when using AI tools. For your convenience, the `.vscode/settings.json` directory is already configured with this encoding.
 - SQL schema is missing foreign keys.
 - Sometimes trying to stop the server hangs it.

## Development notes

### Building the source files

The `.vscode/tasks.json` directory contains helpful build tools. In VSCode you can run the builds by pressing `CTRL`+`SHIFT`+`P` and selecting `Tasks: Run task`. Depending on your environment (Windows/Linux) you should select the appropriate task.

Note that the included `Dockerfile` does not build the source files for you, but it is possible to configure it to do so.

Pre-built gamemode and filterscripts are included in the repository for ease of use.

### MySQL quickstart

Run the command below to launch a mysql database locally.

```
docker network create mynet

docker run -d --network mynet --name mariadb -p 3306:3306 -e MARIADB_ROOT_PASSWORD=*your passowrd* -v mariadb_data:/var/lib/mysql -e MARIADB_DATABASE=samp mariadb:latest
```

**Note that this is not a secure solution for a production environment. It is provided here for testing or local execution only.**

In your `.env` file use:
```
LSG_DB_HOST=127.0.0.1
LSG_DB_USER=root
LSG_DB_PASSWORD=*your password*
LSG_DB_DATABASE=samp
```
### DB seeding

Example commands for DB seeding:

**Linux**:
```
# docker
docker exec -i mariadb mariadb -uroot -p'your password' samp < deployments/db/init.sql
# non-docker
mariadb -uroot -p'your password' samp < deployments/db/init.sql
```
**Windows**:

Use PowerShell:
```
Get-Content deployments/db/init.sql | docker exec -i mariadb mariadb -uroot -p'your password' samp
```

### Updating server files

When a new [open.mp](http://open.mp) server binary is released, you can update the server files directly in the `bin` directory.

## License
This project is licensed under the MIT License © 2026 Rayon Games ([rayon.lt](https://www.rayon.lt))