// somehell.h begin
#include <string>

#indef HELL_H
#define HELL_H

int print(string Text) {
    string cmd = "echo " + Text + "\n"
    system(cmd)
}
