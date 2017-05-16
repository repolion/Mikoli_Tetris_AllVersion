#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>

namespace mikoli {

/*!
 * \brief The Buttons class
 *
 * This class construct an Object that contains a QPushButtons configured
 */
class Buttons{
public:
    //Constructors
    /*!
     * \brief Buttons's constructor without parameters.
     * This constructor uses the constructor with parameters by setting the height to 20 and the width to 10.
     */
    Buttons();

    /*!
     * \brief Buttons's constructor with QWidget as parameter.
     * This constructor is used to create a QPushButton for the "Quick Game".
     * \param fenetre the Widget in which the Button has to appear
     */
    Buttons(QWidget & fenetre);

    /*!
     * \brief Buttons's constructor with parameters.
     * This constructor is used to create a Buttons configured.
     * \param fenetre the Widget in which the Button has to appear
     * \param x the x coordonate of the QPushButton
     * \param y the y coordonate of the QPushButton
     * \param width the QPushButton's with
     * \param height the QPushButton's height
     * \param title the QPushButton's label
     */
    Buttons(QWidget & fenetre,int x,int y,int width,int height,const QString title);

    /*!
     * \brief To set the visibility of the QPushButton.
     * \param visibility QPushButton visible or not
     */
    void setVisibility(bool visibility);

    /*!
     * \brief To get the QPushButton
     */
    QPushButton *getButton();

private:
    /*!
     * \brief The QPushButton
     */
    QPushButton *_button;

};

}
#endif // BUTTONS_H
