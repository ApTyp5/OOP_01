#ifndef ENUMS_H
#define ENUMS_H

enum class Action { Load
                  , Save
                  , Move
                  , Scale
                  , Rotate
                  , Project
                  };

enum class Stage  { AccordingToPlan
                  , IncorrectAction
                  , EmptyInput
                  , InputError
                  , TooLongFnam
                  , RecOpenError
                  , RecCloseError
                  , RecInputError
                  , RecEmptyInput
                  , AllocError
                  , ZeroDiv
                  , FigureUnInit
                  , NullptrReceived
                  , ZeroAngleGiven
                  , SenderOpenError
                  , SenderCloseError
                  , SenderEmptyOutput
                  , SenderOutputError
                  };

#endif // ENUMS_H
