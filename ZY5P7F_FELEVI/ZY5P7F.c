#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>>

int main()
{
    int fd[2]; //Két file diskcriptor van létre hozzva, fd[0] az olvasó, fd[1] az író része a csőnek
    pipe(fd);
    int id = fork(); //Eltárolja a proccess és a child PID-jét, ha 0 akkor a child, ha más adott szám a parent proccess
    if(id != 0)
    {
        close(fd[0]); //Bezárjuk a parent proccess oldaláról az olvasó diskcriptort
        write(fd[1],&id, sizeof(int)); //Bele írjuk a csőbe a parent PID-jét
        close(fd[1]); //Bezárjuk a parent proccess oldaláról az írás diskcriptort
    }
    else
    {
        int x;
        read(fd[0], &x, sizeof(int)); //Bolvassuk a child procces oldaláról a parent PID-jét
        printf("Szulo PID a gyermektol: %d",x);
        write(fd[1],&x,sizeof(int)); //Bele írjuk a csőbe a child PID-jét
        close(fd[0]); //Bezárjuk a child proccess oldaláról az olvasó diskcriptort
        close(fd[1]); //Bezárjuk a child proccess oldaláról az írás diskcriptort
    }

    if(id != 0)
    {
        wait(NULL); //Megvárja míg a child proccess végez a wait(); metódus, majd a NULL paraméter miatt, pedig addig várja még meg nem hal
        close(fd[1]); //Bezárjuk a parent proccess oldaláról az írás diskcriptort
        int y;
        read(fd[0],&y,sizeof(int)); //Bolvassuk a parent procces oldaláról a child PID-jét
        close(fd[0]); //Bezárjuk a parent proccess oldaláról az olvasó diskcriptort
    }

    return 0; // A szülő proccess meghal
}
