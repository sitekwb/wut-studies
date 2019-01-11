package modules.attendancetaking;

import data.Attendance;
import data.Group;
import data.Student;
import mains.Model;
import mains.controllers.PersonController;
import modules.myclasses.MyClassesController;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Date;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 * Module controller class, enabling to take attendance of students of given group.
 * Object of this class is created only by MyClassesController, in which user can choose one group.
 * @see MyClassesController
 */
public class AttendanceTakingController implements ActionListener {

    /**
     * View, initialised by constructor.
     * @see AttendanceTakingView
     */
    private AttendanceTakingView view;
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
     * Reference to group, whose attendance is shown.
     */
    private Group group;
    /**
     * Because of the fact, that there can be only 27 students at once visible, showingState indicates
     * which set of 27 students is this.
     */
    private int showingState;
    /**
     * Is true, when set of students finishes. Else false.
     */
    private boolean endOfGroups;
    /**
     * ArrayList of students, shown currently in view.
     */
    private ArrayList<Student> students;
    /**
     * Get method.
     * @return {@link #view}
     */
    public AttendanceTakingView getView() {
        return view;
    }

    /**
     * Class constructor.
     * @param controller superior controller
     * @param mod model
     * @param gr group
     */
    public AttendanceTakingController(PersonController controller, Model mod, Group gr){
        model = mod;
        cont= controller;
        group = gr;
        view = new AttendanceTakingView();
        showingState = 0;
        endOfGroups = false;
        try {
            show();
        }
        catch(SQLException e){
            view.getErrLabel().setText("Error in connection. Try again.");
        }
        view.getCancelButton().addActionListener(this);
        view.getConfirmButton().addActionListener(this);
        view.getShowNextButton().addActionListener(this);
        view.setVisible(true);
    }

    /**
     * Gets information from model and shows appropriate table with attendance.
     * @throws SQLException if something goes wrong in connection with database.
     */
    private void show() throws SQLException {
        students = model.getStudents(showingState, group);
        int i = 0;
        try {
            for (Student student: students) {
                view.getStudent(i).setText((i + 1) + ". " + student.getName());
                view.getStudent(i).setVisible(true);
                view.getStudent(i).setSelected(true);
                i++;
                if (i >= 27) {
                    break;
                }
            }
            if(i<27) {
                endOfGroups = true;
                do{
                    view.getStudent(i).setVisible(false);
                    i++;
                }while(i<27);
            }
        }
        catch(ArrayIndexOutOfBoundsException e){
            model.signOut();
            cont.signOut();
        }
    }

    /**
     * Checks if given date is correct.
     * @param d date of format DD-MM-YYYY
     * @return true if is correct date, false if not
     */
    private static boolean isDate(String d){
        int day, month,year;
        try {
            day = Integer.parseInt(d.substring(0, 1));
            month = Integer.parseInt(d.substring(3, 4));
            year = Integer.parseInt(d.substring(6, 9));
            new GregorianCalendar(year,month-1,day);
        }
        catch(Exception e){
            return false;
        }
        if(d.charAt(2)!='-' || d.charAt(5)!='-' || d.length()!=10){
            return false;
        }
        return true;
    }
    private static Date toDate(String d){
        int day = Integer.parseInt(d.substring(0, 2));
        int month = Integer.parseInt(d.substring(3, 5));
        int year = Integer.parseInt(d.substring(6, 10));
        return new Date(year-1900,month-1,day);
    }

    /**
     * ActionPerformed method.
     * @param e actionevent caused by one of buttons in view - with commands "Go back", "Refresh" or "Confirm"
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getActionCommand().equals("Go back")){
            MyClassesController myClassesController = new MyClassesController(cont, model,false);
            cont.setWindow(myClassesController.getView());
            view.setVisible(false);
        }
        else if(e.getActionCommand().equals("Confirm")){
            JTextField field = new JTextField();
            field.setFont(new Font("Times New Roman", Font.PLAIN, 40));

            JPanel panel = new JPanel(new BorderLayout(0, 0));

            JLabel label = new JLabel("What is the date of classes? (DD-MM-YYYY)");
            label.setFont(new Font("Times New Roman", Font.PLAIN, 40));

            panel.add(label, BorderLayout.NORTH);
            panel.add(field, BorderLayout.SOUTH);

            int dialogResult = JOptionPane.showConfirmDialog (null, panel);
            String calendar = field.getText();
            while(dialogResult == JOptionPane.YES_OPTION && !isDate(calendar)){
                label.setText("Error, so AGAIN! What is the date of classes? (DD-MM-YYYY)");
                field.setText("");
                dialogResult = JOptionPane.showConfirmDialog (null, panel);
                calendar= field.getText();
            }
            if(dialogResult != JOptionPane.YES_OPTION){
                return ;
            }

            Date date = toDate(calendar);

            int i=0;
            for(Student student: students){
                student.setAttendance(new Attendance(date, view.getStudent(i).isSelected()));
                i++;
                if (i >= 27) {
                    break;
                }
            }
            try{
                model.takeAttendance(students, group);
                view.getErrLabel().setText("Success! Attendance taken");
            }
            catch(SQLException sqlException){
                view.getErrLabel().setText("Error. Try again.");
            }

        }
        else{//show next
            if(endOfGroups){
                showingState=0;
                endOfGroups=false;
            }
            else{
                showingState++;
            }
            try {
                show();
                view.getErrLabel().setText("Next students shown.");
            }
            catch(SQLException sqlException){
                view.getErrLabel().setText("Error! Try again.");
            }
        }

    }
}
