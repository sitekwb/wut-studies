package modules.attendance;

import data.Group;
import data.Student;
import exceptions.ConnException;
import mains.Model;
import mains.controllers.PersonController;
import modules.myclasses.MyClassesController;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Date;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 * Module controller class, showing and enabling to change attendance of students of given group.
 * Object of this class is created only by MyClassesController, in which user can choose one group.
 * @see MyClassesController
 */
public class AttendanceController implements ActionListener {
    /**
     * View, initialised by constructor.
     * @see AttendanceView
     */
    private AttendanceView view;
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
     * ArrayList of students with attendance information.
     */
    private ArrayList<Student> students;

    /**
     * Get method.
     * @return {@link #view}
     */
    public AttendanceView getView() {
        return view;
    }

    /**
     * Class constructor.
     * @param controller superior controller
     * @param mod model
     * @param gr group
     */
    public AttendanceController(PersonController controller, Model mod, Group gr){
        view = new AttendanceView();
        cont = controller;
        model = mod;
        group = gr;
        try {
            show();
        }
        catch(SQLException e){
            view.getErrLabel().setText("Error in connection. Try again.");
        }
        view.getClassLabel().setText(group.getName());

        if(model.getUserType()==Model.UserType.student){
            view.getConfirmButton().setEnabled(false);
            view.getTable().setEnabled(false);
        }

        JTextField textField = new JTextField();
        textField.setFont(new Font("Times New Roman", Font.PLAIN, 30));
        textField.setBorder(new LineBorder(Color.BLACK));
        DefaultCellEditor dce = new DefaultCellEditor( textField );
        for(int i=0; i<view.getTable().getColumnCount()-1;i++) {//the last is bool: present/not-present
            view.getTable().getColumnModel().getColumn(i).setCellEditor(dce);
        }

        view.getCancelButton().addActionListener(this);
        view.getConfirmButton().addActionListener(this);
        view.getRefreshButton().addActionListener(this);
        view.setVisible(true);

    }

    /**
     * Gets information from model and shows appropriate table with attendance.
     * @throws SQLException if something goes wrong in connection with database.
     */
    private void show() throws SQLException {
        students = model.getAttendance(group);
        int i = 0;

        DefaultTableModel tableModel = ((DefaultTableModel)(view.getTable().getModel()));
        tableModel.setRowCount(students.size());

        for (Student student : students) {
            view.getTable().getModel().setValueAt(student.getName(), i, 0);
            view.getTable().getModel().setValueAt(student.getAttendance().getDate(), i, 1);
            view.getTable().getModel().setValueAt(student.getAttendance().getDay(), i, 2);
            view.getTable().getModel().setValueAt(student.getAttendance().isPresent(), i, 3);
            i++;
        }

    }

    private static boolean isDate(String d){
        int day, month,year;
        try {
            year = Integer.parseInt(d.substring(0, 4));
            month = Integer.parseInt(d.substring(5, 7));
            day = Integer.parseInt(d.substring(8, 10));

            new GregorianCalendar(year,month-1,day);
        }
        catch(Exception e){
            return false;
        }
        if(d.charAt(4)!='-' || d.charAt(7)!='-' || d.length()!=10){
            return false;
        }
        return true;
    }
    private static Date toDate(String d){
        int year = Integer.parseInt(d.substring(0, 4));
        int month = Integer.parseInt(d.substring(5, 7));
        int day = Integer.parseInt(d.substring(8, 10));
        return new Date(year-1900,month-1,day);
    }

    /**
     * ActionPerformed method.
     * @param e actionevent caused by one of buttons in view - with commands "Go back", "Refresh" or "Confirm"
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getActionCommand().equals("Go back")){
            if(model.getUserType()==Model.UserType.student){
                cont.setWelcomeWindow();
            }
            else {
                MyClassesController myClassesController = new MyClassesController(cont, model, true);
                cont.setWindow(myClassesController.getView());
            }
            view.setVisible(false);
        }
        else if(e.getActionCommand().equals("Refresh")){
            try {
                show();
            }
            catch(SQLException sqlException){
                view.getErrLabel().setText("Error in connection. Try again.");
            }
        }
        else if(e.getActionCommand().equals("Confirm")){
            int i=0;
            try {
                for (Student student : students) {
                    if (!isDate(view.getTable().getValueAt(i, 1).toString())) {
                        throw new ConnException(ConnException.ErrorTypes.err);
                    }
                    student.getAttendance().setDate(toDate(view.getTable().getValueAt(i, 1).toString()));
                    student.getAttendance().setPresent((boolean) (view.getTable().getValueAt(i, 3)));
                    i++;
                }
                model.updateAttendance(students, group);
                view.getErrLabel().setText("Success! Attendance taken");
            }
            catch(SQLException sqlException){
                view.getErrLabel().setText("Error. Try again.");
            }
            catch(ConnException connException){
                view.getErrLabel().setText("Wrong value in column no."+(i+1)+". Try again");
            }

        }

    }

}
