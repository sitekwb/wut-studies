package init;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * @author Wojciech Sitek
 * @version 1.0
 * @since 1.0, 04/06/2018
 *
 * InitView is a front end class, normal of the package views, visualising the views window
 * (it extends JFrame class),
 * which functions are:
 * <ul>
 *     <li>Asking the user for e-mail and password for logging or registration.</li>
 *     <li>Giving information about login and password to cont (class InitController), implemented in method actionPerformed
 * @link InitView#actionPerformed(ActionEvent e)
 *     </li>
 * </ul>
 *
 */
public class InitView extends JFrame {

    //-----------------------PRIVATE FIELDS---------------------
    /**
     * Button, submitting logging information to controller.
     */
    private JButton logButton;
    /**
     * JTextField with space for entering user's email.
     */
    private JTextField mailField;
    /**
     * JLabel specifying aim of e-mail textField on the right, with its text "E-mail:".
     */
    private JLabel mailLabel;
    /**
     * JPasswordField with space for entering user's password.
     */
    private JPasswordField passField;
    /**
     * JLabel specifying aim of password textField on the right, with its text "Password:".
     */
    private JLabel passLabel;
    /**
     * Button, submitting information about registration to database to controller.
     */
    private JButton registerButton;
    /**
     * JLabel with name of program - "Apograf".
     */
    private JLabel title;
    /**
     * Normally empty label, showing errors of logging or registration
     */
    private JLabel errLabel;


    //------------------GET METHODS--------------------------------
    /**
     * Get method.
     * @return {@link InitView#mailField}
     */
    public JTextField getMailField() {
        return mailField;
    }
    /**
     * Get method.
     * @return {@link InitView#passField}
     */
    public JPasswordField getPasswordField(){
        return passField;
    }
    /**
     * Get method.
     * @return {@link InitView#registerButton}
     */
    public JButton getRegisterButton(){
        return registerButton;
    }
    /**
     * Get method.
     * @return {@link InitView#logButton}
     */
    public JButton getLogButton(){
        return logButton;
    }
    /**
     * Get method.
     * @return {@link InitView#errLabel}
     */
    public JLabel getErrLabel() {
        return errLabel;
    }





    /**
     * Class constructor
     *
     */
    public InitView(){
        super("Apograf - logging window");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        setIconImage(new ImageIcon(getClass().getResource("../images/icon.png")).getImage());
        setBounds((int)screenSize.getWidth()/3,(int)screenSize.getHeight()/5,
                (int)screenSize.getWidth()/3,(int)screenSize.getHeight()*3/4);
        setMinimumSize(new Dimension((int)screenSize.getWidth()/3,(int)screenSize.getHeight()*5/8));
        setMaximumSize(new Dimension((int)screenSize.getWidth(),(int)screenSize.getHeight()));

        title = new JLabel();
        mailField = new JTextField();
        mailLabel = new JLabel();
        passLabel = new JLabel();
        registerButton = new JButton();
        logButton = new JButton();
        passField = new JPasswordField();
        errLabel = new JLabel();


        title.setBackground(Color.yellow);
        title.setFont(new Font("Comic Sans MS", Font.PLAIN, 100));
        title.setForeground(Color.blue);
        title.setText("APOGRAF");
        title.setHorizontalAlignment(JLabel.CENTER);

        mailLabel.setText("E-mail:");
        mailLabel.setHorizontalAlignment(JLabel.RIGHT);
        mailLabel.setFont(new Font("Arial", Font.PLAIN, 40));

        passLabel.setText("Password:");
        passLabel.setHorizontalAlignment(JLabel.RIGHT);
        passLabel.setFont(new Font("Arial", Font.PLAIN, 40));

        mailField.setFont(new Font("Arial", Font.PLAIN, 40));

        passField.setFont(new Font("Arial", Font.PLAIN, 40));

        registerButton.setText("Register");
        registerButton.setFont(new Font("Times New Roman", Font.PLAIN, 40));

        logButton.setText("Log in");
        logButton.setFont(new Font("Times New Roman", Font.PLAIN, 40));

        errLabel.setHorizontalAlignment(JLabel.CENTER);
        errLabel.setFont(new Font("Arial", Font.PLAIN, 35));
        errLabel.setForeground(Color.RED);


        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(logButton, javax.swing.GroupLayout.PREFERRED_SIZE, 369, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(mailLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 406, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(passLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 400, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(layout.createSequentialGroup()
                                                .addGap(19, 31, Short.MAX_VALUE)
                                                .addComponent(registerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 391, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(33, 33, 33))
                                        .addGroup(layout.createSequentialGroup()
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                        .addComponent(passField)
                                                        .addComponent(mailField, javax.swing.GroupLayout.Alignment.TRAILING)))))
                        .addComponent(title, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(errLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addContainerGap())
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(title, javax.swing.GroupLayout.PREFERRED_SIZE, 214, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(mailLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(mailField, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(85, 85, 85)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                        .addComponent(passLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 91, Short.MAX_VALUE)
                                        .addComponent(passField))
                                .addGap(67, 67, 67)
                                .addComponent(errLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 70, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(registerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 312, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(logButton, javax.swing.GroupLayout.PREFERRED_SIZE, 320, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addContainerGap())
        );

        
        setVisible(true);
    }


}
