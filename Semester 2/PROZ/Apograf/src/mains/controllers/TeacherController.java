package mains.controllers;

import mains.Model;
import views.Window;

/**
 * Class starting after logging in, when a person logging is an teacher, but not an admin.
 * Class inherits from PersonController.
 * @see PersonController
 * Class is not public, because we want only {@link Controller} to access this class.
 */
class TeacherController  extends PersonController{
    /**
     * Class constructor, initialises values of PersonController and sets menuButtons (myTeachers)
     * as disabled for teachers (Teachers can view and change only students, not themselfes).
     * @param controller copied value of controller.
     * @param mod copied value of model.
     */
    public TeacherController(Controller controller, Model mod){
        super(controller, mod);
        window.getMenuItem(Window.MenuButtons.myTeachers).setEnabled(false);

    }

}
