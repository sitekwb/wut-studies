package mains.controllers;

import init.InitController;
import mains.Model;
import views.Window;

import javax.swing.*;

/**
 * Class controlling and coordinating work of {@link Model} and View from MVC model of programming in Java.
 * During app life, as a result of interaction with user, it coordinates and changes smaller controllers.
 */
public class Controller {
    /**
     * @see Model
     */
    private Model model;
    /**
     * @see InitController
     */
    private InitController initController;

    /**
     * Public constructor initialising {@link InitController} and setting value to {@link Controller#model}.
     * @param mod value set to private field of type {@link Model}.
     */
    public Controller(Model mod) {
        Window.image = new ImageIcon(getClass().getResource("../../images/icon.png")).getImage();
        model=mod;
        initController = new InitController(this, model);
    }

    /**
     * Method giving possibility to sign out - come back to initial view.
     */
    public void signOut(){
        initController.startViewAgain();
    }

    /**
     * Method called by {@link InitController}, to start new controller, depending on type of user, that has logged in.
     */
    public void startController() {
        switch (model.getUserType()) {
            case student:
                StudentController studentController = new StudentController(this, model);
                break;
            case teacher:
                TeacherController TeacherController = new TeacherController(this, model);
                break;
            case admin:
                AdminController AdminController = new AdminController(this, model);
                break;
        }
    }
}