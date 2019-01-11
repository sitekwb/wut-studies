package mains.controllers;

import data.Student;
import mains.Model;
import modules.myclasses.MyClassesController;
import modules.mystudentsteachers.MyStudentsTeachersController;
import modules.profile.ProfileController;
import modules.timetable.TimetableController;
import views.WelcomeView;
import views.Window;
import views.Window.MenuButtons;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Main controller of all actions after logging in. Listens to actions in menu bar of view class {@link Window}.
 * @see ActionListener
 */
public class PersonController implements ActionListener {

    /**
     * Reference to {@link Model} object.
     */
    protected Model model;
    /**
     * Reference to main {@link Controller} object.
     */
    private Controller cont;
    /**
     * Actually visible module.
     */
    protected Window window;
    /**
     * First view after logging in.
     */
    private WelcomeView welcomeView;

    /**
     * Class constructor, initialising {@link WelcomeView}.
     * @param controller main controller, copied to private parameter.
     * @param mod model, copied to private parameter.
     */
    public PersonController(Controller controller, Model mod) {
        cont = controller;
        model = mod;
        welcomeView = new WelcomeView();
        window = welcomeView;
        try {
            for (int i = 0; i < Window.buttonArraySize; i++) {
                window.getMenuItem(i).addActionListener(this);
            }
        }
        catch(ArrayIndexOutOfBoundsException e){
            model.signOut();
            cont.signOut();
        }

    }

    /**
     * Method actionPerformed from menu bar.
     *
     * @param e parameter of ActionEvent - it can origin from one of the buttons in menu bar.
     */
    public void actionPerformed(ActionEvent e){
        try {
            if(e.getSource() == window.getMenuItem(MenuButtons.exit)){
                JLabel text = new JLabel("Are you sure you want to exit?");
                text.setFont(new Font("Times New Roman", Font.PLAIN, 40));
                int i=JOptionPane.showConfirmDialog(text, text);
                if(i==0) {
                    model.signOut();
                    System.exit(0);
                }
            }
            else {
                Window oldWindow = window;
                if (e.getSource() == window.getMenuItem(MenuButtons.myStudents)){
                    MyStudentsTeachersController myStudentsTeachersController = new MyStudentsTeachersController(this, model, true);
                    window = myStudentsTeachersController.getView();
                }
                else if(e.getSource() == window.getMenuItem(MenuButtons.myTeachers)) {
                    MyStudentsTeachersController myStudentsTeachersController = new MyStudentsTeachersController(this, model, false);
                    window = myStudentsTeachersController.getView();
                } else if (e.getSource() == window.getMenuItem(MenuButtons.signOut)) {
                    signOut();
                } else if (e.getSource() == window.getMenuItem(MenuButtons.takeAttendance)) {
                    MyClassesController myClassesController = new MyClassesController(this, model, false);
                    window = myClassesController.getView();
                } else if (e.getSource() == window.getMenuItem(MenuButtons.timetable)) {
                    TimetableController timetableController = new TimetableController(this, model);
                    window = timetableController.getView();
                } else if (e.getSource() == window.getMenuItem(MenuButtons.viewAttendance)) {
                    MyClassesController myClassesController = new MyClassesController(this, model,true);
                    window = myClassesController.getView();
                } else { //if(e.getSource() == window.getMenuItem(MenuButtons.profile)){
                    ProfileController profileController = new ProfileController(this, model);
                    window = profileController.getView();
                }
                for (int i = 0; i < Window.buttonArraySize; i++) {
                    window.getMenuItem(i).addActionListener(this);
                }

                if(model.getUserType() == Model.UserType.student){
                    window.getMenuItem(MenuButtons.myStudents).setEnabled(false);
                    window.getMenuItem(MenuButtons.takeAttendance).setEnabled(false);
                }
                else if(model.getUserType() == Model.UserType.teacher){
                    window.getMenuItem(Window.MenuButtons.myTeachers).setEnabled(false);
                }

                oldWindow.setVisible(false);
            }
        }
        catch(Exception exception){
            signOut();
        }
    }

    /**
     * Get method.
     * @return {@link #window}
     */
    public Window getWindow(){
        return window;
    }

    /**
     * Set method. Adds action listener for menu bar to newly set window.
     * @param w set value to {@link #window}.
     */
    public void setWindow(Window w){
        window = w;
        for (int i = 0; i < Window.buttonArraySize; i++) {
            window.getMenuItem(i).addActionListener(this);
        }
    }

    /**
     * Sets as a visible window - welcome window
     */
    public void setWelcomeWindow(){
        window = welcomeView;
        window.setVisible(true);
    }

    /**
     * Sign out method. It gives directive to sign out to model, controller and makes window invisible.
     */
    public void signOut(){
        model.signOut();
        window.setVisible(false);
        cont.signOut();
    }

}
