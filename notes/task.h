#ifndef TASK_H
#define TASK_H


#include "notes/note.h"
#include "interfaces/taskinterface.h"

class TaskInterface;
typedef enum {en_attente, en_cours,terminee} Status;// en_attente=0, en_cours=1, terminee=2

/*! Classe Task, classe fille de Note*/
class Task: public Note {
    QString actionToBeDone; /**< Action à réaliser pour la Tâche */
    Status status;  /**< Status de la tâche {en_attente, en_cours,terminee} */
    //{0,1,2,3,4,5}  0:pas de priorité; 5: très élevé :facultatif
    unsigned int priority;  /**< Priorité de la tâche allant de 0:(pas de priorité) à 5 forte priorité */
    // facultatif, date échouante
    QDateTime expired; /**< Date de fin d'une Tâche */
    static const QString type; /**< Attribut statique donnant le type de Note (dérivée) */

public:
    Task(QUuid identifier); /**< Constructeur */
    //Task(const Task& t):Note(t),actionToBeDone(),status(t.getStatus_re()),priority(t.getPriority()),expired(t.getExpired()){}

    const QString& getActionToBeDone() const; /**< Accesseur de l'attribut l'action à réaliser  */
    QString getStatus() const; /**< Accesseur de l'attribut status  */
    unsigned int getStatusInt() const; /**< Accesseur 2 l'attribut status  */
    Status getStatus_re() const; /**< Accesseur 4 de l'attribut du status  */
    unsigned int getPriority() const; /**< Accesseur de l'attribut priorité */
    const QDateTime& getExpired() const; /**< Accesseur de l'attribut  date de fin */

    void setActionToBeDone(const QString& a); /**< Méthode modifiant l'attribut actionToBeDone  */
    void setPriority(unsigned int p); /**< Méthode modifiant l'attribut de priority  */
    void setStatus(Status s); /**< Méthode modifiant l'attribut status  */
    void setExpired(const QDateTime exp); /**< Méthode modifiant l'attribut expired */

    QWidget* getUI() const;   /**< Méthode virtuelle renvoyant l'interface de la Tâche */


    Note* save();
    void restore(Note* n);

    const QString& getType() const; /**< Méthode renvoyant le type de Note (dérivée) */
};

#endif // TASK_H
