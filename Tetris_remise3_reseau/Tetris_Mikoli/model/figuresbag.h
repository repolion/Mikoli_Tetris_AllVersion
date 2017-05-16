#ifndef FIGURESBAG_H
#define FIGURESBAG_H

#include "figure.h"
#include "time.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

namespace mikoli{
/*!
 * \brief The FiguresBag class
 *
 * \ref _nextFigure The Figure that will become the current Figure.
 * \ref _listFigures The list of differents figures that will be played.
 */
class FiguresBag
{
    //Private Attributes
private:
    /*!
     * \brief _nextFigure The Figure that will become the current Figure.
     */
    Figure _nextFigure;
    /*!
     * \brief _listFigures The list of differents figures that will be played.
     */
    std::vector<Figure> _listFigures;

public:
    //Constructor / destructor
    /*!
     * \brief FiguresBag constructor without parameters.
     * This constructor will initialize the FiguresBag with default parameters.
     */
    FiguresBag();

    /*!
     * \brief FiguresBag destructor.
     * Deallocate the memory that was previously reserved for the FiguresBag.
     */
    ~FiguresBag();

    //Getter
    /*!
     * \brief getType() Recover the type of the figure
     * \return The next Figure that will become the current Figure.
     */
    Figure getNextFigure();

    //Other method
    /*!
     * \brief refresh Reinitialize the FiguresBag when the FiguresBag is empty.
     */
    void refresh();

};

}

#endif // FIGURESBAG_H
