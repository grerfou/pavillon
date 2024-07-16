# Notes Robotique_reservoir 


## Quelques Definitions 

### Informatique de reservoir OU Reservoir Computing 

L'informatique de réservoir est un cadre de calcul dérivé de la théorie des réseaux neuronaux récurrents, qui permet de mapper les signaux d'entrée dans des espaces de calcul de dimension supérieure par le biais de la dynamique d'un système fixe et non linéaire appelé réservoir. Une fois que le signal d'entrée est introduit dans le réservoir, qui est traité comme une "boîte noire", un mécanisme de lecture simple est formé pour lire l'état du réservoir et le mettre en correspondance avec la sortie souhaitée. Le premier avantage de ce cadre est que l'apprentissage n'est effectué qu'au stade de la lecture, puisque la dynamique du réservoir est fixe. Le second est que la puissance de calcul des systèmes naturellement disponibles, tant classiques que quantiques, peut être utilisée pour réduire le coût effectif de calcul.

### Roborique Molle OU Soft Robotic 

La robotique molle (en anglais : soft robotics) est un domaine de la robotique. Ce domaine traite des « robots mous » incluant certains types de drones, et construits en matériaux ou structures souples, élastiques ou déformables tels que le silicone, le plastique, le caoutchouc, divers types de gels et autres polymères, tissus élastiques, etc., ou des pièces mécaniques déformables utilisées en robotique, par exemple les ressorts, les élastiques ou les absorbeurs de chocs ou de vibrations.
Ce champ de la robotique semble susciter depuis le début du XXIe siècle un intérêt croissant1 et pourrait contribuer à diminuer le prix de certains robots, et améliorer les réponses de la robotique classique à des questions comme celle de l'« auto-réparation », de la résilience ou de l'autoréplication.

## Récit 

**"Comme la robotique molle utilise des systèmes de motorisation totalement différents, elle est beaucoup plus difficile à contrôler. Certains se musclent, c'est-à-dire qu'ils dilatent ou compriment certaines parties de leur corps pour se développer dans différentes directions, comme une plante ou un animal."**  
Way of being, Non binary machine --> James Bridle

## Reference

- Binary Viz ,Tsoding [Repo](https://github.com/tsoding/binviz), [YT Video](https://www.youtube.com/watch?v=4bM3Gut1hIk)

## Questions :

- Comment une données se mouve t-elle ? 
- Comme [SoftZoo](https://sites.google.com/view/softzoo-iclr-2023/design-space-representation) est t-il possible de vilualizer le mouvement d'une donnée dans un "basssin" ou sur d'autre "matieres" (sable, neige, terre, glace etc..)? 


## Ecriture 


### Premier jets d'idées 

Si on prend l'exemple du projet SoftZoo il ont simuler de maniere informatique le movement de deplacement de certain animaux pour essayer de transcrire dans un mouvement en soft Robotique, aprés cela ils ont ajouter a cette simulation de mouvement un environnement pour visualiser les traces laisser part les mouvement produit, cette experience pourrait aussi bien ressembler à de l'informatique de reservoir. 
Si l'on  considérent toute les données d'un ordinateurs comme une "une particule/un organisme" alors il serait peut etre possible comme dans l'experience de SoftZoo d'en faire des vizualisation, La vizualization de donnée binaire ne serait t-elle pas un point de depart ?  
Dans le projet de Tsoding on peut voir qu'avec un programme de vizualition de données binaires, selon le/les types de fichiers la vizalisation change de tout au tout. Mais si l'on inversait le processus ... Si on simaulais des mouvement qui créeraient des actions ? 
