/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 25/04/25.                                          
**         |___/ 
*/

#include <iostream>
/// 1. La caméra génère un rayon → (x, y)
/// 2. Le rayon touche une primitive ? → Oui ? → continue
/// 3. Je regarde où ça touche et quelle est la normale
/// 4. J’utilise les lumières de la scène pour savoir
///     - Est-ce qu’on voit ce point ?
///     - Est-ce qu’il est dans l’ombre ?
///     - À quel point il est éclairé ?
/// 5. Je combine ça avec la couleur du matériau
/// 6. J’écris la couleur dans l’image finale
///
int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
}

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

