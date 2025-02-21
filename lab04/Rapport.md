# Labo 4 - Buffy

## Instruction de compilation

## Introduction

Bienvenue dans l'univers palpitant de Buffy, la tueuse de vampires ! Imaginez un monde où Buffy doit protéger l'espèce
humaine contre une horde de vampires assoiffés de sang, le tout orchestré dans une simulation tour par tour qui tient en
haleine.

### Présentation de l'application

Dans notre application, nous avons créé une simulation où Buffy (B), les vampires (v) et les humains (h) évoluent sur
une grille. Chacun des protagonistes est un "humanoïde" avec des objectifs bien définis et des comportements uniques. La
taille de la grille ainsi que le nombre d'humains et de vampires peuvent être configurés pour chaque simulation. Une
fois les paramètres définis, nos courageux humanoïdes sont placés aléatoirement sur la grille.

Le menu de l'application est aussi simple que pratique. Il affiche le numéro du tour courant et permet de passer au tour
suivant (en appuyant sur 'n' ou <entrée>), d'effectuer des statistiques (avec 's') ou de quitter le programme (avec '
q'). À chaque tour, chaque humanoïde décide de sa prochaine action, et toutes les actions sont résolues simultanément
pour garantir l'équité. Le résultat de chaque tour est ensuite affiché pour le plaisir des yeux (ou des cauchemars, vu
notre affichage).

### Mécanique des Actions

Chaque humain se déplace au hasard sur la grille, d’une case à la fois. Buffy, notre héroïne, pourchasse et attaque les
vampires. S'il est à une case de distance, elle peut le tuer, sinon, elle le chasse en avançant de deux cases dans sa
direction. Si tous les vampires sont détruits, elle se déplacera au hasard sur la grille comme les humains.

Les vampires, quant à eux, traquent les humains pour les transformer ou les tuer. S'il est à une case de distance, un
vampire peut soit tuer l'humain soit le transformer en vampire (avec une chance sur deux). Sinon, il le chasse en
avançant d'une case dans sa direction. Un humain ne peut donner naissance qu’à un seul vampire. S’il n’y a plus
d’humains à chasser, le vampire reste sur place pour dormir.

### Simulations et Statistiques

Pour les mordus de statistiques, notre application permet de réaliser des simulations en masse (jusqu'à 10’000
simulations) pour évaluer les chances de succès de Buffy. Les statistiques sont obtenues en effectuant ces simulations
pour les mêmes conditions initiales données (taille de la grille, nombre de vampires et d'humains, mais avec un
placement aléatoire), sans afficher le déplacement des humanoïdes. Chaque simulation est arrêtée lorsqu’il n’y a plus de
vampires. Le pourcentage de simulations où au moins un humain reste vivant est calculé et affiché, offrant ainsi un
aperçu de l'efficacité de Buffy dans diverses conditions.

## Implémentation

La conception de notre simulation repose sur un ensemble de classes permettant de factoriser au maximum le code et de
dissocier la gestion de l'interface graphique du comportement des humanoïdes. Chaque classe d’humanoïde référence un
objet Action, caractérisant la prochaine action à effectuer. Cette classe Action possède une
méthode `void execute(Field& f)` permettant d’exécuter l’action courante en influant sur l’environnement, représenté par
la classe Field.

La classe Field permet de faire évoluer les humanoïdes sur une grille, manipulés au moyen d’une liste STL. Cette classe
fournit une méthode pour simuler un tour, déterminant les prochaines actions de chaque humanoïde, exécutant ces actions,
et supprimant les humanoïdes tués. Elle inclut également une méthode pour trouver l’humanoïde le plus proche d’un type
donné.

Elle possède également des attributs pour stocker le nombre de vampires et d'humains. Nous avons décidé de cette
implémentation afin de ne pas avoir à faire des itérations sur la liste et des tests de type pour savoir combien
d'humains et de vampires sont présents sur le terrain. Ces itérations auraient dûes être faites à chaque tour, ce
qui aurait pris un temps non négligeable de calcul. Ici, nous incrémentons et décrémentons les valeurs lorsqu'un
humain ou un vampire est tué ou créé.

### Choix smart pointers

L'emploi de smart pointers dans ce projet est une décision stratégique visant à optimiser la gestion de la mémoire et à
renforcer la sécurité du code. Les smart pointers, tels que `std::shared_ptr` et `std::weak_ptr`, offrent une gestion
automatique de la mémoire, garantissant que les ressources sont correctement libérées lorsque plus aucun objet ne pointe
vers elles. Cela élimine efficacement les risques de fuites de mémoire.

De plus, l'utilisation conjointe de `std::shared_ptr` et `std::weak_ptr` permet de résoudre les problèmes de cycles de
référence. Cette caractéristique est particulièrement pertinente dans le contexte de ce projet, où une instance de
Action doit posséder une référence à un Humanoid et vice versa.

Par ailleurs, l'usage de `std::unique_ptr` assure que chaque Humanoid ne peut posséder qu'une seule instance d'Action à
la
fois. Cette exclusivité est essentielle pour garantir l'intégrité de la logique du programme, car chaque action est
intrinsèquement liée à un Humanoid spécifique. De plus, tout comme les autres smart pointers, `std::unique_ptr` gère
automatiquement la mémoire, ce qui renforce encore la robustesse de la gestion de la mémoire dans le programme.

En somme, l'adoption de smart pointers dans ce projet contribue à une gestion de la mémoire plus efficace et plus sûre,
tout en facilitant la gestion des relations entre les objets `Action` et `Humanoid`.

## Classe `Action`

### Attributs

- **`std::weak_ptr<Humanoid> humanoid_`** : Un pointeur faible vers l'humanoïde qui réalise l'action. L'utilisation d'un
  pointeur faible (weak pointer) permet de ne pas augmenter le compteur de référence de l'humanoïde, ce qui évite les
  cycles de référence potentiels et les fuites de mémoire. Cela signifie que l'action ne revendique pas la propriété de
  l'humanoïde, mais maintient simplement une référence non possédante.

### Méthodes

- **Constructeur** : Prend un `std::shared_ptr<Humanoid>` pour initialiser l'humanoïde qui effectue l'action.

    - ```explicit Action(const std::shared_ptr<Humanoid>& humanoid);```

  Le constructeur initialise l'attribut `humanoid_` avec un pointeur faible dérivé du pointeur partagé fourni. Cela
  permet de créer une action liée à un humanoïde spécifique.

- **Destructeur** : Virtuel par défaut pour permettre la destruction appropriée des objets dérivés.

    - ```virtual ~Action() = default;```

  Ce destructeur virtuel assure que lorsque des objets dérivés de `Action` sont supprimés via un pointeur de
  type `Action*`, les destructeurs des sous-classes sont appelés correctement, ce qui nous permettra une gestion propre
  des ressources.

- **Méthode virtuelle pure `execute`** : Doit être implémentée par les sous-classes pour exécuter l'action dans le
  contexte d'un `Field`.

    - ```virtual void execute(Field& field) = 0;```

  Cette méthode pure virtuelle impose aux classes dérivées de fournir une implémentation de la logique spécifique de
  l'action. Cela garantit que chaque type d'action peut être exécuté dans le contexte du terrain (`Field`).

- **Getter pour l'attribut `humanoid_`** : Retourne le pointeur faible vers l'humanoïde.

    - ```std::weak_ptr<Humanoid> getHumanoid() const;```

  Cette méthode permet d'accéder à l'humanoïde associé à l'action sans affecter le compteur de référence du pointeur
  partagé.

### Précautions de conception

- **Prévention de la copie** : La classe `Action` empêche la copie pour éviter des duplications indésirables et des
  problèmes potentiels de gestion de ressources.
  ```Action(const Action&) = delete;```
  ```Action& operator=(const Action&) = delete;```

## Classe `Kill`

Héritée de `Action`, la classe `Kill` est utilisée pour représenter l'action de tuer un humanoïde. Cette action est
utilisée par Buffy pour tuer les vampires.

### Méthodes

- **Constructeur** : Initialise l'action avec la cible à tuer
    - ```Kill(const std::shared_ptr<Humanoid>& target);```
      Le constructeur prend un paramètre :
      un pointeur partagé vers l'humanoïde qui est la cible de l'action. Le pointeur est converti en pointeur faible
      pour éviter les cycles de références.

- **execute** : Définit comment l'action de tuer est exécutée.
    - ```void execute(Field& field) override;```
      Cette méthode redéfinie implémente la logique spécifique de l'action de tuer dans le contexte du
      terrain (`Field`). Elle décrit ce qui se passe lorsque l'humanoïde tueur attaque et tue la cible.

## Classe `Bite`

Héritée de `Kill`, la classe `Bite` représente l'action de mordre par un humanoïde.
L'action de mordre sera utilisée par les vampires pour attaquer les humains et les transformer ou les tuer.

### Méthodes

- **Constructeur** : Initialise l'action avec le chasseur et la cible.
  -```Bite(const std::shared_ptr<Humanoid> &target);```
  Le constructeur prend un paramètre :
  un pointeur partagé vers l'humanoïde qui est la cible de l'action. Le pointeur est converti en pointeur faible
  pour éviter les cycles de références.

- **execute** : Définit comment l'action de mordre est exécutée.
    - ```void execute(Field &field) override;```
      Cette méthode redéfinie implémente la logique spécifique de l'action de mordre dans le contexte du
      terrain (`Field`). Elle décrit ce qui se passe lorsque l'humanoïde chasseur mord la cible, par exemple,
      transformer un humain en vampire.

## Classe `Move`

Héritée de `Action`, `Move` permet de représenter le déplacement d'un humanoïde. Tous les humanoïdes peuvent se
déplacer, mais les déplacements sont différents en fonction du type d'humanoïde.

### Attributs

- **`size_t range_`** : La portée du déplacement possible.
- **`std::optional<Vec2D>`** : L'éventuelle position de la cible à atteindre.

### Méthodes

- **Constructeur** : Initialise le déplacement avec une portée et éventuellement une personne qui se déplace et une
  cible.

    - ```Move(size_t range, const std::shared_ptr<Humanoid>& mover, const std::optional<Vec2D> target = std::nullopt)
  ;```

  Le constructeur prend trois paramètres : une portée (range) définissant la distance maximale que peut parcourir
  l'humanoïde, un pointeur partagé vers l'humanoïde qui effectue le déplacement (mover) et un `std::optional` pour
  la position de la cible à atteindre. (target). Les pointeurs
  sont convertis en pointeurs faibles pour éviter les cycles de
  référence. La position de la cible est facultative, car tous les déplacements ne nécessitent pas une cible.

- **getPossiblePositions** : Calcule les positions possibles pour le déplacement.

    - ```std::vector<Vec2D> getPossiblePositions(const Vec2D& position, const Field& field);```

  Cette méthode privée calcule les positions possibles pour le déplacement en respectant la portée et les contraintes du
  champ (`Field`). Elle retourne un vecteur de pointeurs constants vers des objets `Vec2D` représentant les positions
  possibles.

- **execute** : Définit comment l'action de déplacement est exécutée.

    - ```void execute(Field& field) override;```

  Cette méthode redéfinie implémente la logique spécifique de l'action de déplacement dans le contexte du
  terrain (`Field`). Elle décrit ce qui se passe lorsque l'humanoïde se déplace, en tenant compte de la portée et des
  positions possibles.

## Classe `Humanoid`

La classe `Humanoid` représente un humanoïde générique dans la simulation. Elle contient les attributs et méthodes de
base pour les humanoïdes, qui peuvent être hérités et spécialisés par des sous-classes comme `Buffy`.

### Attributs

- **`std::unique_ptr<Action> nextAction_`** : L'action que l'humanoïde va effectuer au prochain tour.
- **`Vec2D position_`** : La position actuelle de l'humanoïde sur le champ.
- **`bool alive_`** : L'état de vie de l'humanoïde. Cet attribut est utile pour savoir si l'humanoïde est toujours en
  vie et, si nécessaire, le retirer du champ.

### Méthodes

- **Constructeur** : Initialise l'humanoïde avec une position donnée.

    - ```Humanoid(const Vec2D& position);```

  Le constructeur initialise l'humanoïde à une position spécifiée sur le champ.
- **Destructeur** : Virtuel par défaut pour permettre la destruction appropriée des objets dérivés.

    - ```virtual ~Humanoid() = default;```

  Ce destructeur virtuel assure que lorsque des objets dérivés de `Humanoid` sont supprimés via un pointeur de
  type `Humanoid*`, les destructeurs des sous-classes sont appelés correctement, ce qui nous permettra une gestion
  propre
  des ressources.
- **chooseAction** : Choisit une action en fonction du contexte.

    - ```virtual Action* chooseAction(const Field& field) = 0;```

  Cette méthode virtuelle pure permet à l'humanoïde de choisir une action à effectuer en fonction de la situation sur le
  terrain (`Field`). Les sous-classes doivent fournir une implémentation de cette méthode.
- **executeAction** : Exécute l'action actuelle de l'humanoïde.

    - ```void executeAction(Field& field);```

  Cette méthode exécute l'action actuelle de l'humanoïde sur le terrain (`Field`).
- **kill** : Tue l'humanoïde.

    - ```virtual void kill(Field& field);```

  Cette méthode virtuelle permet à l'humanoïde de mourir. Les sous-classes peuvent
  fournir une implémentation spécifique pour cette action.
- **getActionRange** : Retourne la portée de mouvement.

    - ```virtual size_t getActionRange() const;```

  Cette méthode virtuelle retourne la distance maximale que l'humanoïde peut appliquer à son action durant un tour.
  Les sous-classes peuvent la redéfinir. Sa valeur par défaut est de 1.

## Classe `Buffy`

Héritée de `Humanoid`, Buffy possède des capacités spéciales pour se déplacer et attaquer dans la simulation.

### Méthodes

- **chooseAction** : Choisit une action en fonction du contexte.

    - ```void chooseAction(const Field& field);```

  Cette méthode permet à Buffy de choisir une action à effectuer en fonction de la situation sur le terrain (`Field`)
  . Soit bouger simplement comme un humain normal, ou bien aller chasser et tuer des vampires.

- **getActionRange** : Retourne la portée de mouvement de Buffy.

    - ```size_t getActionRange() const;```

  Cette méthode retourne la distance maximale que Buffy peut parcourir en un tour.

- **getType** : Retourne le type "Buffy".

    - ```std::string getType() const;```

  Cette méthode retourne une chaîne de caractères indiquant le type d'humanoïde, en l'occurrence "Buffy". Cette
  méthode est utilisée pour l'affichage.
- **kill** : Tue l'humain, mais Buffy ne peut pas mourir.

    - ```void kill(Field& field) override;```

  Cette méthode redéfinit `kill` de `Humanoid` pour signifier que Buffy ne peut pas mourir.

## Classe `Human`

Héritée de `Humanoid`, cette classe représente les humains avec des comportements et capacités spécifiques. Elle permet
de définir les actions et caractéristiques propres aux humains dans la simulation.

### Méthodes

- **Constructeur** : Initialise l'humain avec une position donnée.

    - ```explicit Human(const Vec2D& position);```

  Le constructeur prend une position initiale et initialise l'humanoïde à cette position.

- **getType** : Retourne le type "Human".

    - ```std::string getType() override;```

  Cette méthode retourne une chaîne de caractères indiquant le type d'humanoïde, en l'occurrence "Human".

- **chooseAction** : Choisit une action en fonction du contexte.

    - ```Action* chooseAction(const Field& field) override;```

  Cette méthode permet à l'humain de choisir une action à effectuer en fonction de la situation sur le
  terrain (`Field`). Les humains se déplacent aléatoirement sur le terrain.

- **kill** : Tue l'humain.

    - ```void kill(Field& field) override;```

  Cette méthode définit ce qui se passe lorsque l'humain meurt sur le terrain (`Field`).

## Classe `Vampire`

Héritée de `Humanoid`, les vampires ont des capacités uniques de mouvement et d'attaque dans la simulation.

### Méthodes

- **Constructeur** : Initialise le vampire avec une position donnée.

    - ```explicit Vampire(const Vec2D& position);```

  Le constructeur prend une position initiale et initialise le vampire à cette position.

- **getType** : Retourne le type "Vampire".

    - ```std::string getType() override;```

  Cette méthode retourne une chaîne de caractères indiquant le type d'humanoïde, en l'occurrence "Vampire".

- **chooseAction** : Choisit aléatoire une action en fonction du contexte.

    - ```Action* chooseAction(const Field& field) override;```

  Cette méthode permet au vampire de choisir une action à effectuer en fonction de la situation sur le
  terrain (`Field`). Soit chasser des humains et les mordre, soit se reposer.

- **kill** : Tue le vampire.

    - ```void kill(Field& field) override;```

  Cette méthode définit ce qui se passe lorsque le vampire meurt sur le terrain (`Field`).

## Classe `Field`

Représente le champ de jeu où tous les humanoïdes interagissent. Cette classe est responsable de la gestion des
humanoïdes et de l'évolution de la simulation. Elle place l'ensemble des humanoïdes sur le champ et gère les actions de
chaque tour.

### Constructeur

- **Field(size_t height, size_t width, size_t nbVampire, size_t nbHuman)** : Initialise le champ avec les dimensions
  données et le nombre de vampires et d'humains. `Field` placera alors les humanoïdes aléatoirement sur le champ.

### Attributs

- **humanoids** : Liste de humanoïdes actifs dans le champ.
- **height_**, **width_** : Dimensions du champ.
- **nbVampire_**, **nbHuman_** : Nombre initial de vampires et d'humains.
- **turn_** : Numéro du tour actuel.

### Méthodes

- **getTurn** : Retourne le numéro du tour actuel.

    - ```size_t getTurn() const;```

- **nextTurn** : Passe la simulation au tour suivant et met à jour l'état du champ.

    - ```int nextTurn();```

- **findClosestHumanoid** : Recherche l'humanoïde le plus proche d'un type donné.

    - ```template<typename T> ```
      ```std::shared_ptr<T> findClosestHumanoid(const std::shared_ptr<Humanoid>& hunter, size_t& distance) const;```
- **fieldToStringVector** : Convertit l'état actuel du champ en un vecteur de chaînes de caractères.

    - ```std::vector<std::vector<<std::string>> fieldToStringVector() const;```

  Cette méthode permet de transformer notre field en un vecteur de vecteurs de chaînes de caractères. Cela permet
  la représentation graphique de notre field.
- **addHumanoid** : Ajoute un humanoïde au champ.

    - ```void addHumanoid(std::shared_ptr<Humanoid> humanoid);```

  Permet d'ajouter un humanoïde dans la liste du field.
- **vampireBorn, humanKilled, vampireKilled**
    - ```void vampireBorn();```
    - ```void humanKilled();```
    - ```void vampireKilled();```

  Ces méthodes permettent de gérer le nombre d'humains et de vampires sur le terrain. Elles sont appelées lorsqu'un
  humain est tué ou transformé en vampire, ou lorsqu'un vampire est tué.
- **isFinished** : Vérifie si la simulation est terminée.

    - ```Status isFinished() const;```

  Cette méthode vérifie si la simulation est terminée, c'est-à-dire si tous les vampires ont été tués ou s'il n'y a
  plus d'humains. Elle retourne un `Status` indiquant l'état de la simulation.

## Classe `FieldController`

La classe `FieldController` gère les opérations liées à un champ de jeu, comme l'affichage et le contrôle des tours dans
une simulation.

### Constructeur

- **FieldController(Field& field)** : Initialise le contrôleur avec le champ donné.

    - ```explicit FieldController(Field& field);```

  Le constructeur prend une référence à un objet `Field` et initialise le contrôleur pour ce champ.

### Attributs

- **currentField** : Référence au champ actuel.
- **running** : Indique si la simulation est en cours.
- **initialNbHuman** : Nombre initial d'humains.
- **initialNbVampire** : Nombre initial de vampires.

### Méthodes

- **displayFieldToString** : Convertit l'état actuel du champ en une chaîne de caractères.

    - ```static std::string displayFieldToString(const Field& field);```

  Cette méthode génère une représentation textuelle de l'état actuel du champ de jeu.

- **start** : Démarre la simulation.

    - ```void start();```

  Cette méthode initialise et démarre la simulation.

- **stop** : Arrête la simulation.

    - ```void stop();```

  Cette méthode arrête la simulation en cours.

- **nextTurn** : Passe au tour suivant dans la simulation.

- ```void nextTurn();```

Cette méthode passe au tour suivant, mettant à jour l'état du champ et des entités.

- **handleCommand** : Gère les commandes données par l'utilisateur.

    - ```void handleCommand(const Command& command);```

  Cette méthode traite les commandes saisies par l'utilisateur pour contrôler la simulation.

- **printHorizontalBorder** : Imprime la bordure horizontale du champ.

    - ```static void printHorizontalBorder(const Field& field, std::string& output);```

  Cette méthode ajoute une bordure horizontale à la représentation textuelle du champ.

- **printVerticalBorder** : Imprime la bordure verticale du champ.

    - ```static void printVerticalBorder(const Field& field, std::string& output);```

  Cette méthode ajoute une bordure verticale à la représentation textuelle du champ.

- **display** : Affiche le champ actuel sur la console.

    - ```static void display(const Field& field);```

  Cette méthode affiche le champ et ses entités sur la console.

## Structure `FieldStatsCalculator`

La structure `FieldStatsCalculator` fournit des fonctionnalités pour simuler
et calculer des statistiques sur le champ de jeu. Elle est utilisée pour évaluer les résultats de différentes
configurations de simulation.

### Méthodes

- **simulate** : Simule la configuration du champ de jeu un certain nombre de fois et retourne les statistiques de
  victoire face aux vampires.

    - ```static double simulate(size_t height, size_t width, size_t nbVampire, size_t nbHuman, size_t nbSimulations=10000);```

## Structure `Random`

La structure `Random` fournit des méthodes statiques pour générer des nombres aléatoires utilisés dans la simulation.

### Attributs

- **rng** : Générateur de nombres aléatoires de Mersenne Twister.

    - ```static std::mt19937 rng;```

  Ce dernier prend comme seed le temps actuel.

### Méthodes

- **generate** : Génère un nombre entier aléatoire entre `min` et `max`.

    - ```static int generate(int min, int max);```

  Cette méthode retourne un entier aléatoire compris entre `min` et `max` `[min, max]`. Elle lance une exception
  `invalid_argument`
  si `min` est supérieur ou égal à `max`.

- **generateFrom0** : Génère un nombre entier aléatoire entre 0 et `max` `[0, max]`.

    - ```static int generateFrom0(size_t max);```

  Cette méthode retourne un entier aléatoire compris entre 0 et `max`.

- **randomBool** : Génère un booléen aléatoire.

    - ```static bool randomBool();```

  Cette méthode retourne soit `true` soit `false` de manière aléatoire.

## Structure `Vec2D`

La structure `Vec2D` représente un vecteur ou un point dans un espace 2D, utilisé pour manipuler des positions ou des
mouvements dans la simulation.

### Attributs

- **x, y** : Coordonnées du vecteur.

### Méthodes

- **Constructeur** : Initialise le vecteur avec des coordonnées données.

    - ```Vec2D(int x_, int y_);```

  Ce constructeur initialise un vecteur avec les coordonnées spécifiées `x_` et `y_`.

- **Constructeur par défaut** : Initialise le vecteur à (0, 0).

    - ```Vec2D();```

  Ce constructeur initialise un vecteur avec les coordonnées (0, 0).

- **calculateDistance** : Calcule la distance au carré entre deux vecteurs.

    - ```size_t calculateDistance(const Vec2D& other) const;```

  Cette méthode retourne la distance au carré entre le vecteur actuel et un autre vecteur `other`.

- **absoluteDistance** : Calcule la distance absolue entre deux vecteurs.

    - ```Vec2D absoluteDistance(const Vec2D& other);```

  Cette méthode retourne un vecteur représentant la distance absolue entre le vecteur actuel et un autre
  vecteur `other`.

- **subtraction** : Soustrait un autre vecteur du vecteur actuel.

    - ```Vec2D subtraction(const Vec2D& other) const;```

  Cette méthode retourne un nouveau vecteur qui est la différence entre le vecteur actuel et un autre vecteur `other`.

- **addition** : Additionne un autre vecteur au vecteur actuel.

    - ```Vec2D addition(const Vec2D& other) const;```

  Cette méthode retourne un nouveau vecteur qui est la somme du vecteur actuel et d'un autre vecteur `other`.

- **getDirection** : Retourne la direction unitaire entre deux vecteurs.

    - ```Vec2D getDirection(const Vec2D& other) const;```

  Cette méthode retourne un vecteur représentant la direction unitaire du vecteur actuel vers un autre vecteur `other`.

- **getRandomUnitaryDirection** : Génère un vecteur aléatoire.

    - ```Vec2D getRandomVector(size_t maxX, size_t maxY);```

  Cette méthode retourne un vecteur aléatoire entre (0, 0) et (maxX, maxY).

## Enum `Status`

L'énumération `Status` est utilisé pour représenter le statut du jeu.

- `RUNNING` Lorsque que le jeu est en cours d'exécution
- `LOSE` Lorsque le jeu est fini et les humains ont perdu (plus d'humain en jeu).
- `WIN` Lorsque le jeu est fini et les humains ont gagné (plus de vampires en jeu).

## Tests

Bien sûr ! Voici un tableau de test pour la simulation de Buffy la tueuse de vampires. Ce tableau inclut différents
scénarios pour vérifier que la simulation se comporte comme prévu.

### Tests
Voici le tableau mis à jour, incluant les règles de déplacement et d'interaction :

| Test                                                                                                               | Résultat attendu et observé                                                                                                                                                        |
|:-------------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Lancement du programme avec une taille fournie, un nombre d'humains et un nombre de vampires                       | Le `Field` apparaît avec le nombre d'humains et de vampires souhaités ainsi qu'une Buffy. Tous ces humanoïdes ont des positions aléatoires.                                        |
| L'utilisateur lance le programme avec des arguments invalides (ex: manquants, valeurs < 0, valeurs non numériques) | Un message d'erreur apparaît et le programme s'arrête.                                                                                                                             |
| L'utilisateur lance le programme avec des arguments valides mais une ou plusieurs valeurs vaut 0.                  | Un message d'erreur apparaît et le programme s'arrête.                                                                                                                             |
| L'utilisateur entre l'input `<< n >>`                                                                              | L'affichage se met à jour, chaque humanoïde de la simulation a reçu une action et l'a effectuée.                                                                                   |
| L'utilisateur appuie sur sa touche entrée                                                                          | L'affichage se met à jour, chaque humanoïde de la simulation a reçu une action et l'a effectuée.                                                                                   |
| L'utilisateur entre l'input `<< q >>`                                                                              | Le programme se ferme sans soucis, toutes les allocations dynamiques sont bien désallouées.                                                                                        |
| L'utilisateur entre l'input `<< s >>`                                                                              | Un nombre de simulations fixé (10'000) est démarré avec les paramètres rentrés au lancement de l'application. Une fois terminées, le pourcentage de victoire de Buffy est affiché. |
| L'humanoïde humain passe un tour de simulation.                                                                    | L'Human se déplace d'une case aléatoirement et reste à l'intérieur du terrain de jeu.                                                                                              |
| Un vampire se trouve à plus d'une case de l'humain le plus proche.                                                 | Le vampire se rapproche de l'humain le plus proche d'une case.                                                                                                                     |
| Un vampire se trouve à une case d'un humain.                                                                       | Le vampire mord l'humain. L'humain a une chance sur deux d'être transformé en vampire, sinon il est tué. Ni le vampire ni l'humain ne se déplacent après cette action.             |
| Buffy se trouve à plus de deux cases d'un vampire.                                                                 | Buffy se rapproche du vampire le plus proche en se déplaçant de deux cases vers lui.                                                                                               |
| Buffy se trouve à deux cases ou moins d'un vampire.                                                                | Buffy tue le vampire sans se déplacer.                                                                                                                                             |
| Il n'y a plus d'humains.                                                                                           | Les vampires ne se déplacent plus.                                                                                                                                                 |
| Il n'y a plus de vampires.                                                                                         | Buffy et les humains restants se déplacent aléatoirement d'une case par tour.                                                                                                      |  

## Résultats

Les statistiques à la suite des 10'000 simulations montrent que Buffy réussit à sauver au moins un humain dans ~45%
des cas. Plusieurs simulations ont été run pour vérifier la fiabilité de ces statistiques.

|  **Résultats des statistiques**  |
|:--------------------------------:|
|              44.48               |
|              44.66               |
|              44.85               |
|              44.59               |
|              44.26               |
|              43.97               |
|               43.2               |
|              44.27               |
|              44.37               |
|              44.29               |

Moyenne : 44.294

Médiane : 44.33

SD : 0.456

On peut observer que la médiane et la moyenne sont très proches, ce qui indique une distribution relativement
symétrique et normale. La déviation standard est également faible, ce qui suggère que les résultats sont cohérents
et les simulations n'ont pas des résultats soudainement incohérents.

## Conclusion

En conclusion, ce laboratoire a été une occasion précieuse pour nous de mettre en pratique et d'approfondir notre
compréhension des concepts avancés de C++. Nous avons exploré en détail l'utilisation des smart pointers, un outil
puissant pour la gestion de la mémoire, qui a permis d'assurer la robustesse de notre simulation en évitant les fuites
de mémoire et les problèmes de cycles de référence.

Nous avons également mis en œuvre l'héritage et le polymorphisme, des concepts fondamentaux de la programmation orientée
objet, pour créer une hiérarchie de classes représentant les différents types d'humanoïdes et d'actions dans notre
simulation. Cela a permis de factoriser le code et de faciliter son évolution et sa maintenance.

De plus, nous avons utilisé des techniques avancées de programmation, comme les méthodes virtuelles pures et les
pointeurs faibles, pour gérer les relations entre les objets de manière flexible et sécurisée. Nous avons également
utilisé des structures pour représenter des vecteurs 2D et des nombres aléatoires, démontrant l'efficacité de ces outils
pour simplifier le code et améliorer sa lisibilité.

En outre, nous avons mis en place un système de simulation et de calcul de statistiques, qui nous a permis d'évaluer les
performances de notre simulation et d'optimiser ses paramètres. Cela a été une excellente occasion de mettre en pratique
nos compétences en analyse de données.

Enfin, ce laboratoire a été une excellente occasion de découvrir et d'apprécier l'univers de Buffy, la tueuse de
vampires. Nous avons pu intégrer des éléments de cet univers dans notre simulation, ce qui a ajouté une dimension
ludique à notre travail et a rendu l'expérience d'apprentissage encore plus enrichissante.

Pour certains d'entre nous, comme Massimo, qui n'a aucune culture générale, ce fut une belle découverte. Cela a souligné
l'importance de la culture générale dans le développement de logiciels, car elle peut fournir une source d'inspiration
précieuse pour la conception de nos projets.

En somme, ce laboratoire a été une expérience d'apprentissage enrichissante et stimulante, qui nous a permis de
renforcer nos compétences en C++ et de découvrir de nouvelles façons d'utiliser ce langage pour créer des applications
robustes et efficaces. Nous sommes impatients de mettre en pratique ce que nous avons appris dans nos futurs projets.
