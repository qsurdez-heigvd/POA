# Rapport Lab02 Squadron

Author: Jallon Sarah, Surdez Quentin

## Introduction

Dans ce laboratoire nous devons créer une escadrille de vaisseaux provenant de la franchise "Star Wars". Cela 
demande l'utilisation de classes ainsi que l'utilisation du concept du polymorphisme. 

L'escadrille, quant à elle, 
doit implémenter différentes méthodes afin de changer son contenu, de calculer la consommation de carburant ou 
encore de définir quel est le chef de l'escadrille. 

## Instruction de compilation

Pour compiler le laboratoire, nous avons choisi d'avoir une structure de dossier avec un __cmake__. Pour comiler le 
projet nous avons utilisé les versions suivantes de __cmake__ et de __gcc__:

```
    cmake version 3.29.0
    Apple clang version 15.0.0 (clang-1500.1.0.2.5)
```

Pour compiler le programme, exécuter la suite d'instructions suivantes : 

```bash
    mkdir build
    cd build
    cmake .. -G "Unix Makefiles"
    make
```

Pour lancer le programme, exécuter la commande suivante dans le dossier `build` : 

```bash
    ./squadron
```

## Choix d'implémentation

Le laboratoire a été divisé en deux grosses parties. La première étant l'implémentation des différents `Ship`. Ici, 
les concepts d'héritages et factorisations ont été importants. 

La deuxième partie s'est concentrée sur le `Squadron`.
Le concept d'encapsulation a été le plus important durant cette étape du projet. 

Ci-dessous, nous développerons les deux parties et les différents choix d'implémentation que nous avons fait.

### Ship

Comme dit précédemment, l'héritage est le coeur de l'implémentation des différents `Ship`. En effet, ce qui est 
commun à tous les enfants de `Ship` doit se trouver dans cette classe, ce qui n'est pas commun aux différents 
vaisseaux doit se trouver dans les classes filles.

#### Attribut

Cependant, quelques spécificités du langage ont pu nous poser problèmes. En effet, chaque vaisseau possède un numéro 
d'usine. Ce numéro doit être incrémenté à chaque fois qu'un vaisseau est créé. Pour cela, nous avons utilisé une 
variable statique dans chaque classe concrète afin de pouvoir l'assigner à chaque vaisseau.

Nous avions commencé par mettre l'attribut `factoryNumber` en protected dans la classe `Ship`. Cela a pour 
conséquence que la classe propriétaire de l'attribut perd son contrôle dessus. Nous avons donc réfléchi à une 
différente manière de faire. 

Nous est venu l'idée de créer un constrcteur dans `Ship` qui assignerait cette valeur et le constructeur est appelé 
par les classes enfants avec en paramètre le numéro d'usine. Nous avons gardé ce choix d'implémentation.

Aucun des attributs identitaire des vaisseaux n'a été défini en statique. Nous avons préféré retourner dans des 
getters dédiés. 

##### Constructeur

Les sous-populations de `Ship` sont définis comme suit : 
- Des vaisseaux sans cargo
- Des vaisseaux avec cargo

Les vaisseaux avec cargo ont une quantité de cargo max qu'ils peuvent transporter. Cette quantité maximale est 
retournée par un getter. 

Le constructeur de ces vaisseaux va prendre en paramètre la quantité de cargo qui est 
donnée au vaisseau ainsi que la quantité max que celui-ci peut transporter. Une exception est levée si la quantité 
transportée est plus grande que la quantité maximale.

Une classe intermédiaire `TIEBaseModel` a aussi été créée pour factoriser le code des vaisseaux de type TIE.

Nous avons choisi, après être allé nous renseigner dans le livre de référence suivant: `Deciphering Object-Oriented
Programming with C++` par Dorothy R. Kirk, de déclarer les constrcteurs de nos classes abstraites donc contenant des
méthodes purement virtuelles ou conceptuellement abstraites, n'ayant pas de méthodes purement virtuelles mais se
se comportant comme telles, en `protected`. Cela permet aux classes concrètes de les utiliser sans en donner
la possibilité au niveau de l'utilisateur.ice.

### Squadron

Comme dit précédemment, nous nous sommes focalisés sur l'encapsulation du code pour réalisé `Squadron`. Il a été 
très important d'analyser les différentes répétitions de code et de les factoriser. Cependant, nous n'avons pas 
utilisé de lambda. Nous faisons l'hypothèse que cela nous aurait permis d'éviter autant de boucles mais ne les ayant 
pas vu en cours et ne 
sachant pas les utiliser nous avons décidé de les laisser de côté.

#### Structure

Nous avons décidé d'utiliser la structure de donnée d'une liste chaînée pour stocker les informations des vaisseaux 
dans l'escadrille. Pour ce faire nous avons une structure inter `Node` qui stock un pointeur sur `Ship` comme valeur 
et un pointeur sur le prochain `Node`. Cela nous permet de facilement parcourir la liste et de pouvoir ajouter ou 
supprimer aisément des éléments.

#### Attributs

Plusieurs attributs sont nécessaires afin que la liste chaînée puisse être implémentée. Nous avons un pointeur sur 
un `Node` qui est la head de notre liste. Comme nous n'utilisons pas d'itérateurs, nous n'avons pas de `Node` 
pointeur sur l'avant début. Nous avons décidé de stocker la taille de la liste afin de faire de simple check pour 
lorsque l'utilisateur ou l'utilisatrice souhaite accéder au i-ème objet de la liste.

Le nom et le chef sont des attributs obligatoires selon la donnée du laboratoire. Le nom est toujours présent pour 
une escadrille, mais une escadrille peut ne pas avoir de chef. 
Il y a un seul chef à la fois et on ne peut attribuer un chef sans 
remove l'actuel.

Dans la structure `Node`, nous avons un pointeur sur `Ship`. Cependant, ce pointeur n'a pas le qualificatif `const`. 
Ainsi, nos opérateurs prennent des `Ship&` et non des `const Ship&`. Cette décision a été longuement discuté avec le 
professeur et comme nous souhaitons changer l'instance du `Ship` mais pas son pointeur, nous avons décidé de ne pas 
lui donner le qualificatif de `const`.

#### Méthodes

Les différentes méthodes publiques sont celles qui ont été nécessaires de créer afin que le laboratoire puisse 
répondre aux exigences. 

Nous avons aussi concentré notre effort sur des méthodes privées qui sont là pour permettre de factoriser le code un 
maximum. Ces dernières permettent de créer, de faire une deep copy, de move ou encore de delete un `Squadron`.

### Utils

Nous avons créé un namespace afin de réunir quelques fonctions utiles pour le formattage dans l'`ostream`. Ce 
dernier se nomme `ostreamUtils`.

## Tests

Nous avons décidé de tester notre programme avec des tests unitaires. Nous avons utilisé la librairie `GoogleTest` 
afin de réaliser ces tests. Nous avons testé les différentes méthodes de `Squadron` et par extension celles de 
`Ship` afin de vérifier que tout fonctionne correctement.

Les résultats sont comme attendus et aucune erreur n'a pu être relevée.

## Conclusion

Nous avons pu explorer dans ce laboratoire les notions de polymorphisme et d'encapsulation de code. Nous avons pu 
créer un `Squadron` ainsi que des `Ship` avec des caractéristiques différentes. 