# Tempest-atari-1981

Remake du jeu d'arcade Tempest Atari version 1981

# Compilation

Pout télécharger le code et le compiler sur tous les systèmes vous pouvez utiliser les instructions suivantes:

	git clone --recurse-submodule git@git.unistra.fr:s.foerster/tempest-atari-1981.git
	mkdir Build
	cd Build
	cmake ../tempest-atari-1981
	make -j 12

# Lancer le jeu (Toujours depuis le répertoir Build)

	./Tempest/Tempest

# Utilisation

	Par précaution, les effets sonores sont désactivés pour éviter des erreurs connus de segmentation qui peuvent arriver avec SDL Audio.
	Vous pouvez les activer en modifiant la variable global SOUND au début du main.cpp en la mettant à 1.
	
	ATTENTION: Si vous activez les effets sonores, il faut avoir installé les packages libasound et libpulse:
	> sudo apt-get install libasound2-dev libpulse-dev
	Sinon, ces derniers seront automatiquement désactivés au démarrage du jeu.


	Contrôles: 

	Choix du niveau au menu de démarrage en scrollant avec la molette.
	Molette souris pour changer de couloir
	Espace pour tirer des missiles
	Z pour le SuperZapper
	Escape pour Pause