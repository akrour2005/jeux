#ifndef MENU_H
#define MENU_H

class Menu {
public:
    void handleInput();              // G�re les entr�es du menu
    int getSelectedOption();         // Retourne l'option s�lectionn�e
    bool isStartSelected() const;    // V�rifie si "Start" a �t� s�lectionn�
};

#endif // MENU_H
