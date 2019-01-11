package modules.timetable;

import javax.swing.*;
import java.awt.*;

/**
 * Appropriate view to TimetableController.
 * @see TimetableController
 * @see views.Window
 */
public class TimetableView extends views.Window {
    private javax.swing.JButton cancelButton;
    private javax.swing.JButton confirmButton;
    private javax.swing.JLabel errLabel;
    private javax.swing.JScrollPane jScrollPane;
    private javax.swing.JTable jTable;
    private JButton refreshButton;
    private javax.swing.JLabel classLabel;
    private javax.swing.JLabel title1;
    /**
     * Get method.
     * @return cancelButton
     */
    JButton getCancelButton(){
        return cancelButton;
    }

    /**
     * Get method.
     * @return classLabel.
     */
    JLabel getClassLabel(){
        return classLabel;
    }

    /**
     * Get method.
     * @return confirmButton
     */
    JButton getConfirmButton(){
        return confirmButton;
    }

    /**
     * Get method.
     * @return errLabel
     */
    JLabel getErrLabel(){
        return errLabel;
    }

    /**
     * Get method.
     * @return refreshButton
     */
    JButton getRefreshButton(){
        return refreshButton;
    }

    /**
     * Get method.
     * @return table
     */
    JTable getTable(){ return jTable; }

    /**
     * Class constructor
     */
    public TimetableView(){
        refreshButton = new javax.swing.JButton();
        cancelButton = new javax.swing.JButton();
        confirmButton = new javax.swing.JButton();
        classLabel = new javax.swing.JLabel();
        errLabel = new javax.swing.JLabel();
        jScrollPane = new javax.swing.JScrollPane();
        jTable = new javax.swing.JTable();
        title1 = new javax.swing.JLabel();


        refreshButton.setText("Refresh");
        refreshButton.setFont(new Font("Times New Roman", Font.PLAIN, 30));

        cancelButton.setText("Go back");
        cancelButton.setFont(new Font("Times New Roman", Font.PLAIN, 30));

        confirmButton.setText("Confirm");
        confirmButton.setFont(new Font("Times New Roman", Font.PLAIN, 30));

        classLabel.setText("");
        classLabel.setFont(new Font("Times New Roman", Font.PLAIN, 40));

        errLabel.setText("Your timetable:");
        errLabel.setFont(new Font("Times New Roman", Font.PLAIN, 40));

        jTable.getTableHeader().setFont(new Font("Times New Roman", Font.PLAIN, 40));
        jTable.setFont(new Font("Times New Roman", Font.PLAIN, 30));
        jTable.setRowHeight(40);
        jTable.setModel(new javax.swing.table.DefaultTableModel(
                new Object [][] {

                },
                new String [] {
                        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
                }
        ) {
            Class[] types = new Class [] {
                    String.class, String.class, String.class, String.class, String.class, String.class,
                    String.class
            };
            boolean[] canEdit = new boolean [] {
                    false, false,false,false,false,false,false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jScrollPane.setViewportView(jTable);

        title1.setText("Timetable");
        title1.setFont(new Font("Times New Roman", Font.PLAIN, 100));

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(jScrollPane)
                                        .addGroup(layout.createSequentialGroup()
                                                .addComponent(errLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 1358, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addComponent(cancelButton, javax.swing.GroupLayout.PREFERRED_SIZE, 301, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(confirmButton, javax.swing.GroupLayout.PREFERRED_SIZE, 296, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(refreshButton, javax.swing.GroupLayout.PREFERRED_SIZE, 223, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addContainerGap())))
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(classLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 1380, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addContainerGap())
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                        .addGap(10, 10, 10)
                                        .addComponent(title1, javax.swing.GroupLayout.PREFERRED_SIZE, 905, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addContainerGap(1317, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(7, 7, 7)
                                .addComponent(classLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 101, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(errLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(confirmButton, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(refreshButton, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(cancelButton, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(18, 18, 18)
                                .addComponent(jScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 833, Short.MAX_VALUE))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                        .addGap(10, 10, 10)
                                        .addComponent(title1, javax.swing.GroupLayout.PREFERRED_SIZE, 101, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addContainerGap(945, Short.MAX_VALUE)))
        );

    }
}
