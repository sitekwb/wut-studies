package mains.controllers;

import mains.Model;
import views.Window.MenuButtons;

/**
 * Class starting after logging in, when a person logging is an student. Class inherits from PersonController.
 * @see PersonController
 * Class is not public, because we want only {@link Controller} to access this class.
 */
class StudentController extends PersonController {
    /**
     * Class constructor, initialises values of PersonController and sets menuButtons (myStudents and takeAttendance)
     * as disabled for students.
     * @param controller copied value of controller.
     * @param mod copied value of model.
     */
    public StudentController(Controller controller, Model mod) {
        super(controller, mod);
        window.getMenuItem(MenuButtons.myStudents).setEnabled(false);
        window.getMenuItem(MenuButtons.takeAttendance).setEnabled(false);
    }


}
