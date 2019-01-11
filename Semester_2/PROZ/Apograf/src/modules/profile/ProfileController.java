package modules.profile;

import exceptions.ConnException;
import mains.controllers.PersonController;
import mains.Model;
import data.Student;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.sql.SQLException;

/**
 * Module controller class, showing and enabling to edit information my profile.
 * @see ActionListener
 */
public class ProfileController implements ActionListener,KeyListener {
    /**
     * Superior controller
     * @see PersonController
     */
    private PersonController cont;
    /**
     * Reference to model
     * @see Model
     */
    private Model model;
    /**
     * View, initialised by constructor.
     * @see ProfileView
     */
    private ProfileView view;

    /**
     * Get method.
     * @return {@link #view}
     */
    public ProfileView getView(){
        return view;
    }

    /**
     * Class constructor.
     * @param controller superior controller
     * @param mod model
     * @throws ConnException unknown errors may occur
     */
    public ProfileController(PersonController controller, Model mod) throws ConnException{
        cont = controller;
        model = mod;
        view = new ProfileView();
        //internal frame settings

        setShowingSettings("Password: ***");
        for(int i=0;i<5;i++){
            view.getButton(i).addActionListener(this);
        }
        view.getTextField(0).addKeyListener(this);
        view.getTextField(1).addKeyListener(this);


    }

    /**
     * Method which sets settings, shown by view.
     * @param errMsg message set as text for password/error label in view
     * @throws ConnException unknown errors may occur
     */
    private void setShowingSettings(String errMsg)  {
        try {
            for (int i = 0; i < 5; i++) {
                view.getButton(i).setVisible(true);
                view.getLabel(i).setVisible(true);
                view.getTextField(i).setVisible(false);

            }
            view.getLabel(0).setText(errMsg);//errLabel
            view.getButton(0).setText("Change password");

            view.getTextField(0).setText("");
            view.getTextField(1).setText("");

            view.getLabel(1).setText("Mail: " + model.getMe().getMail());
            view.getButton(1).setText("Change mail");

            view.getLabel(2).setText("Name: " + model.getMe().getName());

            switch (model.getUserType()) {
                case student:
                    view.getButton(2).setText("Ask for change of name");

                    view.getLabel(3).setText("Student ID: " + ((Student) (model.getMe())).getStudentID());
                    view.getButton(3).setText("Ask for change of student ID");

                    view.getLabel(4).setText("Degree: " + ((Student) (model.getMe())).getGenGroup());
                    view.getButton(4).setText("Ask for change of degree");
                    break;
                case teacher:
                    view.getButton(2).setText("Ask for change of name");

                    view.getLabel(3).setText("Type of user: TEACHER");
                    view.getButton(3).setVisible(false);

                    view.getLabel(4).setVisible(false);
                    view.getButton(4).setVisible(false);
                    break;
                case admin:
                default:
                    view.getButton(2).setText("Change name");

                    view.getLabel(3).setText("Type of user: ADMIN");
                    view.getButton(3).setVisible(false);

                    view.getLabel(4).setVisible(false);
                    view.getButton(4).setVisible(false);
            }
        }
        catch (ConnException connException) {
            model.signOut();
            cont.signOut();
        }
    }


    /**
     * Checks if string is an integer
     * @param s string value
     * @return true if s is an integer, false if not.
     */
    private static boolean isInteger(String s){
        try{
            Integer.parseInt(s);
        }
        catch(NumberFormatException e){
            return false;
        }
        return true;
    }

    /**
     * Values possible to change
     */
    private static String labels[] = {"password","mail", "name", "student ID", "group"};
    /**
     * Indicates which value user wants to change
     */
    private int typeOfChange;

    /**
     * Action performed method.
     * @param e can get actions from buttons with commands "Confirm", "Cancel"
     * @see ProfileView
     */
    public void actionPerformed(ActionEvent e){
        try {
            if (e.getActionCommand().equals("Confirm")) {//pressed Confirm
                changeValue();
            }
            else if(e.getActionCommand().equals("Cancel")) {
                setShowingSettings("Action cancelled");
            }
            else {//action to change something
                for (int i = 0; i < 5; i++) {
                    if (e.getSource() == view.getButton(i)) {
                        typeOfChange = i;
                        view.getLabel(0).setText("New " + labels[i] + ": ");
                        view.getLabel(0).setVisible(true);

                        view.getTextField(0).setVisible(true);


                        view.getButton(0).setText("Confirm");
                        view.getButton(0).setVisible(true);

                        view.getButton(1).setText("Cancel");
                        view.getButton(1).setVisible(true);

                        for (int j = 2; j < 5; j++) {
                            view.getLabel(j).setVisible(false);
                            view.getTextField(j).setVisible(false);
                            view.getButton(j).setVisible(false);
                        }
                        if (i == 0) {//password
                            view.getLabel(1).setText("New password once again: ");
                            view.getTextField(1).setVisible(true);
                        } else {
                            view.getLabel(1).setVisible(false);
                            view.getTextField(1).setVisible(false);
                        }
                        break;
                    }
                }
            }//actions in state showing
        }
        catch (Exception exception) {
            model.signOut();
            cont.signOut();
        }

    }//actionPerformed

    public void keyTyped(KeyEvent e){

    }
    public void keyReleased(KeyEvent e){

    }
    public void keyPressed(KeyEvent e){
        if(e.getKeyCode() == KeyEvent.VK_ENTER ){
            changeValue();
        }
    }

    private void changeValue() {
        try {
            String errMsg="Password: ***";
            String val = view.getTextField(0).getText();
            switch (typeOfChange) {
                case 0://password
                    if (val.equals(view.getTextField(1).getText()) &&
                            !val.isEmpty()) {
                        model.changePass(model.getMe(), val);
                        errMsg = "Success! Password changed.";
                    } else {
                        errMsg = "Error! Not the same or empty values.";
                    }
                    break;
                case 1://mail

                    if (!val.isEmpty()) {
                        model.changeMail(model.getMe(), val);
                        errMsg = "Success! Mail changed.";
                    } else {
                        errMsg = "Error! Empty value.";
                    }

                    break;
                case 2://name

                    if (!val.isEmpty()) {
                        if (model.getUserType() == Model.UserType.admin) {
                            model.changeName(model.getMe(), val);
                            errMsg = "Success! Name changed.";
                        } else {
                            model.askForChange(val, "name");
                            errMsg = "Success! Asked for name change.";
                        }
                    } else {
                        errMsg = "Error! Empty value.";
                    }

                    break;
                case 3://studentID

                    if (!val.isEmpty() && isInteger(val)) {
                        model.askForChange(val, "student_id");
                        errMsg = "Success! Asked for student ID change.";
                    } else {
                        errMsg = "Error! Empty or not integer value.";
                    }

                    break;
                case 4:
                default://class
                    if (!val.isEmpty()) {
                        model.askForChange(val, "class");
                        errMsg = "Success! Asked for group change.";
                    } else {
                        errMsg = "Error! Empty value.";
                    }
                    break;
            }
            setShowingSettings(errMsg);
        }
        catch(ConnException connException){
            setShowingSettings(connException.getErrorMessage());
        }
        catch (Exception exception) {
            model.signOut();
            cont.signOut();
        }
    }

}
