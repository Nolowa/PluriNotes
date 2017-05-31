#include "notes/noteholder.h"

void NoteHolder::update(const Note &newVersion){
    lastVersion = &newVersion;
}
