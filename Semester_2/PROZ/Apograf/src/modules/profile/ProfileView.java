package modules.profile;

import exceptions.ConnException;

import javax.swing.*;
import java.awt.*;

import static exceptions.ConnException.ErrorTypes.err;

/**
 * Appropriate view to ProfileController.
 * @see ProfileController
 * @see views.Window
 */
public class ProfileView extends views.Window {
    private javax.swing.JButton jButton[];
    private javax.swing.JLabel jLabel[];
    private javax.swing.JTextField jTextField[];
    private javax.swing.JLabel title;

    /**
     * Get method.
     * @param i number of button, from 0 to 4
     * @return button[i]
     * @throws ConnException when i is inappropriate
     */
    public JButton getButton(int i) throws ConnException{
        if(i>4 || i<0) throw new ConnException(err);
        return jButton[i];
    }
    /**
     * Get method.
     * @param i number of text field, from 0 to 4
     * @return textField[i]
     * @throws ConnException when i is inappropriate
     */
    public JTextField getTextField(int i)throws ConnException{
        if(i>4 || i<0) throw new ConnException(err);
        return jTextField[i];
    }
    /**
     * Get method.
     * @param i number of label, from 0 to 4
     * @return label[i]
     * @throws ConnException when i is inappropriate
     */
    public JLabel getLabel(int i) throws ConnException{
        if(i>4 || i<0) throw new ConnException(err);
        return jLabel[i];
    }

    /**
     * Class constructor.
     */
    public ProfileView(){
        title = new javax.swing.JLabel();

        jLabel = new JLabel [5] ;
        jTextField = new JTextField[5];
        jButton = new JButton[5];

        GridLayout layout = new GridLayout(6,3);
        setLayout(layout);

        title.setText("PROFILE");
        title.setFont(new Font("Comic Sans MS",Font.PLAIN, 100));

        add(title);
        layout.addLayoutComponent("Title",title);
        //empty labels to manage gridLayout
        JLabel lab1 = new JLabel();
        JLabel lab2 = new JLabel();
        add(lab1);
        add(lab2);
        layout.addLayoutComponent("Empty JLabel", lab1);
        layout.addLayoutComponent("Empty JLabel", lab2);
        for(int i=0;i<5;i++){
            jLabel[i]=new JLabel();
            jLabel[i].setFont(new Font("Times New Roman", Font.PLAIN,40));
            add(jLabel[i]);
            layout.addLayoutComponent("Label "+(i+1),jLabel[i]);

            jTextField[i]=new JTextField();
            jTextField[i].setFont(new Font("Times New Roman", Font.PLAIN,40));
            add(jTextField[i]);
            layout.addLayoutComponent("TextField "+(i+1),jTextField[i]);

            jButton[i]=new JButton();
            jButton[i].setFont(new Font("Times New Roman", Font.PLAIN,40));
            add(jButton[i]);
            layout.addLayoutComponent("Button "+(i+1),jButton[i]);
        }



        setVisible(true);
    }



}
