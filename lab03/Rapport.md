# Laboratoire 3:  Rivière

###### Auteurs: REDACTED & Quentin Surdez & REDACTED

## Introduction

Le but de ce laboratoire est de créer une application en C++ en mode console permettant à l’utilisateur d’introduire
des commandes pour embarquer et débarquer des personnes sur un bateau, ainsi que le déplacer d'une rive à l'autre.
Le cadre de l'application est le suivant: un père, une mère, leur deux garçons, leur deux filles, un policier et un
voleur se trouvent sur une rive. Le but est de déplacer tout le monde sur l'autre rive à l'aide d'un bateau en
respectant les règles suivantes:

- Il ne peut y avoir que deux personnes au maximum sur le bateau.
- Les enfants et le voleur ne peuvent piloter le bateau (mais peuvent y monter lorsqu’il est à quai).
- Le voleur ne peut pas rester en contact avec un membre de la famille si le policier n'est pas présent.
- Les fils ne peuvent rester seuls avec leur mère si le père n’est pas présent.
- Les filles ne peuvent rester seules avec leur père si la mère n’est pas présente.
  Cette application doit être réalisée en tirant parti des concepts de la programmation orientée objet.

## Instructions de Compilation

Pour ce laboratoire, nous avons utilisé une structure avec un `cmake`. Pour compiler le programme, nous avons
utilisé les versions suivantes des outils:

- `cmake` version 3.22.1
- `gcc` version 11.4.0

Pour compiler le programme, vous pouvez exécuter les commandes suivantes en commencant au niveau du dossier
contenant le fichier `CMakeLists.txt`:

```shell
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
```

Pour lancer le programme principal contenant l'application modélisant la traversée de la rivière, vous pouvez
exécuter la commande suivante:

```shell
./river 
```

## Choix de Conception

### Persons

Les différentes personnes présentes dans le problème sont modélisées par la classe anstraite `Person`. Cette classe
contient les attributs communs à toutes les personnes, à savoir le nom de la personne. Elle déclare aussi une méthode
virtuelle pure `isStateValid` qui prend un container en paramètre. Cette méthode doit être implémentée par les
sous-classes de `Person` et permet de vérifier si l'état actuel de la personne est valide par rapport à un container,
c'est-à-dire si les règles propres à la personne sont respectées. Nous avons décidé de stocker les règles propres à
une personne directement dans la classe de cette personne. Ainsi, il est simple de modifier les règles propres à une
personne en modifiant directement la classe de cette personne.

La classe `IndependantPerson` hérite de `Person` et modélise les personnes qui n'ont pas de règles particulières à
respecter et qui peuvent donc être déplacées sans contraintes. Cela concerne le père, la mère et le policier. De plus,
toutes ces personnes sont celles qui peuvent piloter le bateau. Dans la situation actuelle, il n'y a pas besoin de
classes spécialisées pour ces différents types de personne puisqu'elles sont toutes indépendantes et ne dépendent de
personne.

Les classes `Child` et `Thief` héritent de `Person` et modélisent les enfants et le voleur respectivement.
Contrairement à la classe `IndependantPerson`, ces classes
contiennent des pointeurs vers les personnes dont elles dépendent. Ces personnes sont le policier pour le voleur et
le père et la mère pour les enfants. La classe `Child` a aussi des sous-classes `Boy` et `Girl` qui modélisent les
garçons et les filles respectivement, puique ceux-ci ont des règles spécifiques à respecter. Les classes `Boy`, `Girl`
et `Thief` implémentent la méthode `isStateValid` en utilisant les pointeurs vers les personnes dont elles dépendent
pour vérifier si leurs règles respectives sont respectées.

Pour les classes qui représentent des personnes dépendantes, nous avons décidé de stocker les messages d'erreur
correspondant aux règles non respectées dans des constantes statiques directement dans la classe. Cela permet de
centraliser les messages d'erreur et de les rendre facilement accessibles dans le programme.

### StateResult

La classe StateResult est utilisée pour représenter le résultat d'une opération ou d'une action dans le programme. Elle
contient deux membres principaux : `state` et `error`.

- `state` est un booléen qui indique si l'opération a réussi ou
  non. Si `state` est true, cela signifie que l'opération a réussi. Si `state` est false, cela signifie que l'opération
  a échoué.
- `error` est un std::optional<std::string> qui contient un message d'erreur si l'opération a échoué. Si state
  est true, error est généralement vide, d'où l'utilité d'voir un type optionnel. Si `state` est false, `error` contient
  généralement un message d'erreur qui explique pourquoi l'opération a échoué.

L'utilisation de cette classe permet de gérer les erreurs de manière plus structurée et explicite. Au lieu de simplement
retourner true ou false pour indiquer le succès ou l'échec d'une opération, on peut également fournir un message
d'erreur détaillé qui peut aider à comprendre pourquoi l'opération a échoué. Cela nous est utile en particulier pour
remonter des erreurs à l'utilisateur de l'application.

### Containers

### Controller

<!---
Tant que le bateau est à l'arrêt, pas besoin d'un conducteur. 
Si la commande n'existe pas -> erreur
-->

## Tests

Les différents tests que nous avons effectués ont été fait avec le programme en connaissant l'output attendu.
Ici, nous décrirons ces différents tests ainsi que leur output.

### Person tests

Dans cette partie nous nous focaliserons sur les relations entre les différentes `Person` et regarderons si
leur comportement est celui attendu.

| Description                                        | Result                                   | Status |
|----------------------------------------------------|------------------------------------------|--------|
| Le garçon peut monter seul<br/>dans le bateau      | Garçon seul dans le bateau               | ok     |
| Le garçon ne peut pas conduire le bateau           | Erreur pas de conducteur                 | ok     |
| Le garçon ne peut pas être seul<br/>avec sa mère   | Erreur garçon seul avec sa mère          | ok     |
| Le garçon peut être avec son père                  | Garçon et père dans le bateau            | ok     |
| La fille peut monter seule<br/>dans le bateau      | Fille seule dans le bateau               | ok     |
| La fille ne peut pas conduire le bateau            | Erreur pas de conducteur                 | ok     |
| La fille ne peut pas être seule<br/>avec son père  | Erreur fille seule avec son père         | ok     |
| La fille peut être avec sa mère                    | Fille et mère sur le bateau              | ok     |
| Le voleur peut être seul sur le bateau             | Voleur seul sur le bateau                | ok     |
| Le voleur ne peut pas conduire le bateau           | Erreur pas de conducteur                 | ok     |
| Le voleur ne peut être seul sans le policier       | Erreur voleur doit être avec le policier | ok     |
| Le voleur peut être sur le bateau avec le policier | Policier et voleur sur le bateau         | ok     |

### Container tests

Dans cette partie nous nous concentrerons sur les états et les changements que peuvent survenir au sein des
`Container` modélisant les rives ainsi que le bateau. Nous observerons si leur
comportement coïncide avec celui attendu.

| Description                                                           | Result                                        | Status |
|-----------------------------------------------------------------------|-----------------------------------------------|--------|
| Un maximum de deux personnes peuvent être ajoutées dans le bateau     | Erreur déjà deux personnes sur le bateau      | ok     |
| Le bateau ne peut pas bouger si un conducteur n'est pas présent       | Erreur aucun conducteur pour bouger le bateau | ok     |
| Le bateau bouge sur la rive opposée mlorsqu'un conducteur est présent | Le bateau bouge sur la rive opposée           | ok     |

### Controller tests

Dans cette partie nous nous focaliserons sur les commandes que doit gérer le `Controller`. Nous regarderons si
l'exécution de ces commandes est celle attendue.

| Description                                                                                                                   | Result                                                            | Status |
|-------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------|--------|
| Lorsque p est appuyé, l'état du jeu s'affiche                                                                                 | L'état du jeu est affiché                                         | ok     |
| Lorsque e et un nom d'une personne sont entrés en commande, la personne agit selon ses contraintes pour monter dans le bateau | La personne agit selon ses contraintes pour monter dans le bateau | ok     |
| Lorsque d et un nom d'une personne sont entrés en commande, la personne agit selon ses contraintes pour descendre du bateau   | La personne agit selon ses contraintes pour descendre du bateau   | ok     |
| Lorsque m est appuyé et qu'un conducteur est présent dans le bateau, le bateau se déplace                                     | Le bateau se déplace                                              | ok     |
| Lorsque r est appuyé, le jeu se réinitialise à son état 0                                                                     | Le jeu est réinitialisé                                           | ok     |
| Lorsque q est appuyé, le jeu se termine                                                                                       | Le programme se termine                                           | ok     |
| Lorsque h est appuyé, le menu du jeu s'afficher                                                                               | Le menu du jeu s'affiche                                          | ok     |


### Solution du jeu

La solution suivante est censée permettre faire passer toutes les personnes sur l'autre rive avec les contraintes
présentes : 

- e voleur
- e policier
- m
- d voleur
- m
- e fille1
- m
- d policier
- d fille1
- e voleur
- e policier
- m
- d policier
- d voleur
- e fille2
- e mere
- m
- d fille2
- m
- e pere
- m
- d mere
- m
- d pere
- e voleur
- e policier
- m
- d policier
- d voleur
- e mere
- m
- e pere
- m
- d mere
- m
- e fils1
- m
- d pere
- d fils1
- e voleur
- e policier
- m
- d policier
- d voleur
- e fils2
- e policier
- m
- d fils2
- m
- e voleur
- m
- d policier
- d voleur

Après cette suite de commande, le jeu est gagné. Le comportement est comme attendu.


## Conclusion

Dans ce laboratoire, nous avons pu implémenter une application en C++ en mode console permettant à l’utilisateur
de déplacer des personnes d'une rive à l'autre en respectant certaines règles. Nous avons utilisé les concepts de la
programmation orientée objet au mieux pour modéliser les différentes entités du problème. Le bateau et les rives
sont représentés par des containers et nous avons assuré le respect des règles en utilisant un controller. Enfin, le
programme principal permet à l'utilisateur d'introduire toutes les commandes prévues et de voir l'évolution de la
situation à chaque étape. Ce dernier se comporte comme attendu et respecte les contraintes du problème.