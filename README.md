# Los Santos Gyvenimas

<center>

![logo](https://i.imgur.com/IxNr6XB.png) 

</center>

🇱🇹 **Los Santos Gyvenimas** - vienas didžiausių lietuviškų SA:MP serverių, aktyviai veikęs 2010-2026 metais. 

[LSGyvenimas.lt](http://www.lsgyvenimas.lt)


## Installation instructions


**Prerequisites**: Docker, Git.

 **Clone the repository**:
- `git clone https://github.com/vsbenas/lsg`
- `cd lsg`

**Set up database**:
- If you don't have a MySQL server, follow the instructions under [MySQL quickstart](#mysql-quickstart).
- Rename `.env.example` to `.env`. Fill out the details and make sure to change the `RCON_PASSWORD` variable.
- Create database with name given to `LSG_DB_DATABASE` in `.env`.
- Set up the database using the `deployments/db/init.sql` script. See [DB Seeding](#db-seeding) for example commands.

**Build and launch**:

- Create a docker network `docker network create mynet`
- Build the image: `docker build -t lsg .`
- Run the server: `docker run --network mynet -p 7777:7777/udp --env-file .env -it --name lsg lsg`

You're done! You can now join the server at `127.0.0.1:7777`.

**Set up networking**:

The previous setup hides real user IPs due to docker networking. This can cause issues with proxy checks, bans etc. 

To make sure everything work smoothly, you should run your production server on Linux and use `--network host` for the run command.

## Known issues
 - SA:MP MySQL plugin does not connect to MySQL servers requiring SSL. Running a MySQL server locally helps to avoid this problem.
 - Email and SMS sending is disabled because they require outside integrations.
 - Source files must be edited in `windows1257` encoding, otherwise Lithuanian characters will get corrupted. This is prone to happen when using AI tools. For your convenience, the `.vscode/settings.json` directory is already configured with this encoding.
 - SQL schema is missing foreign keys.
 - Sometimes trying to stop the server hangs it.

## Development notes

### Building the source files

The `.vscode/tasks.json` file contains helpful build macros. By default you can build the gamemode in VSCode on Windows by pressing `CTRL`+`SHIFT`+`B`. For alternative build scripts, such as building on Linux or building other source files press `CTRL`+`SHIFT`+`P` and select `Tasks: Run task`.

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
LSG_DB_HOST=mariadb
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