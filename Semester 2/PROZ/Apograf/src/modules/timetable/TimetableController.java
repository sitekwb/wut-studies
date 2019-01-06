package modules.timetable;

import data.Group;
import data.Person;
import data.Student;
import data.Teacher;
import exceptions.ConnException;
import mains.Model;
import mains.controllers.PersonController;
import modules.mystudentsteachers.MyStudentsTeachersView;
import views.Window;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.util.ArrayList;



/**
 * Module controller class, showing timetable.
 * @see ActionListener
 */
public class TimetableController implements ActionListener {
    /**
     * View, initialised by constructor.
     * @see TimetableView
     */
    private TimetableView view;
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
     * ArrayList of groups
     */
    private ArrayList<Group> groups;

    /**
     * Get method
     * @return {@link #view}
     */
    public Window getView() {
        return view;
    }

    /**
     * Public class constructor
     * @param controller controller
     * @param mod model
     */
    public TimetableController(PersonController controller, Model mod){
        view = new TimetableView();
        cont = controller;
        model = mod;

        DefaultTableModel tableModel = ((DefaultTableModel)(view.getTable().getModel()));

        JTextField textField = new JTextField();
        textField.setFont(new Font("Times New Roman", Font.PLAIN, 30));
        textField.setBorder(new LineBorder(Color.BLACK));
        DefaultCellEditor dce = new DefaultCellEditor( textField );
        for(int i=0; i<view.getTable().getColumnCount();i++) {
            view.getTable().getColumnModel().getColumn(i).setCellEditor(dce);
        }

        view.getConfirmButton().setEnabled(false);
        view.getTable().setEnabled(false);
        try {
            show();
        }
        catch(SQLException e){
            view.getErrLabel().setText("Error in connection. Try again.");
        }


        view.getCancelButton().addActionListener(this);
        view.getRefreshButton().addActionListener(this);
        view.setVisible(true);

    }
    /**
     * Gets information from model and shows appropriate groups in table.
     * @throws SQLException if something goes wrong in connection with database.
     */

    private void show() throws SQLException {
        groups = model.getTimetable();
        DefaultTableModel tableModel = ((DefaultTableModel)(view.getTable().getModel()));
        tableModel.setRowCount(groups.size());
        int row[] = new int[7];
        for (Group group: groups) {
            view.getTable().getModel().setValueAt(group.getTime()+" "+group.getName(), row[group.getDayId()], group.getDayId());
            row[group.getDayId()]++;
        }
        int max=0;
        for(int e: row){
            if(e>max){
                max=e;
            }
        }
        tableModel.setRowCount(max);

    }


    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getActionCommand().equals("Go back")){
            cont.setWelcomeWindow();
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
    }
}
