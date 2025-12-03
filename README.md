Simulateur de Schéma Électronique — Guide d’Utilisation

Ce projet permet de saisir une équation booléenne, de visualiser automatiquement le schéma logique correspondant et d’afficher les chronogrammes des signaux en entrée et en sortie.

📌 Prérequis

Système d’exploitation : Windows, Linux ou macOS

Environnement : Qt Creator

Compilateur : Compatible C++17 (MinGW, MSVC ou GCC)

🚀 Procédure de lancement

Ouvrir Qt Creator.

Aller dans Fichier > Ouvrir un projet, puis sélectionner le fichier CMakeLists.txt.

Configurer le projet avec le kit souhaité.

Lancer la compilation.

Après compilation, un dossier build est généré. À l’intérieur :

Créer un fichier simulation.txt

Y inscrire les valeurs des variables selon la syntaxe définie (ex : X=0 Y=1 Z=0).

✏️ Saisie de l'équation

Au lancement, une fenêtre s’ouvre avec une barre de saisie en haut.
L'utilisateur y entre une équation booléenne en respectant les règles suivantes :

Variables : X, Y, Z

Opérateurs : and, or, xor, not

Exemple :

S = (X and Y) or not Z


Valider l’équation avec la touche Entrée.

🧩 Visualisation du Schéma

Une fois l'équation validée :

Le schéma logique se dessine automatiquement.

Les symboles normalisés sont utilisés.

L’état (0 ou 1) de chaque nœud est affiché en temps réel.

⏱️ Chronogramme

La partie inférieure de la fenêtre affiche les chronogrammes des signaux :

Entrées : X, Y, Z

Sortie : S

Les courbes sont générées à partir du fichier simulation.txt.
Chaque graduation représente 50 ns.
