package views;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;

/**
 * Class from View part of MVC model, inherited by all other view classes.
 * @see JFrame
 */
public class Window extends JFrame {
    protected JMenuBar menuBar;
    protected JMenu modulesMenu;
    protected JMenu attendanceMenu;
    protected JMenuItem exitButton;
    protected JMenuItem myStudentsButton;
    protected JMenuItem myTeachersButton;
    protected JMenu optionsMenu;
    protected JMenuItem signOutButton;
    protected JMenuItem takeAttendanceButton;
    protected JMenuItem timetableButton;
    protected JMenuItem viewAttendanceButton;
    protected JMenuItem profileButton;


    /**
     * Array of menuItems, initialized in constructor of this class. Created for easier access to menuItems.
     */
    protected JMenuItem buttonArray[];

    /**
     * Internal enum class, indicating names for menu items. This corresponds to array {@link Window#buttonArray}.
     */
    public enum MenuButtons{exit,myStudents,myTeachers,signOut,takeAttendance,timetable,
        viewAttendance,profile};
    /**
     * Static value, initialized in constructor, indicating size of array {@link Window#buttonArray}.
     */
    public static int buttonArraySize;

    public static Image image;
    /**
     * Get method for items of menu, created in constructor.
     * It makes use of {@link Window#buttonArray} and {@link Window.MenuButtons}.
     * @param button {@link Window.MenuButtons} value, indicating, which menu item to get
     * @return Corresponding menu item
     */
    public JMenuItem getMenuItem(MenuButtons button){
        return buttonArray[button.ordinal()];
    }

    /**
     Get method for items of menu, created in constructor.
     * It makes use of {@link Window#buttonArray} and {@link Window.MenuButtons}.
     * @param i integer value, indicating, which menu item to get
     * @return Corresponding menu item
     * @throws ArrayIndexOutOfBoundsException thrown if parameter i is incorrect
     */
    public JMenuItem getMenuItem(int i) throws ArrayIndexOutOfBoundsException{
        if(i<0 || i>buttonArraySize-1){
            throw new ArrayIndexOutOfBoundsException();
        }
        return buttonArray[i];
    }

    /**
     * Public constructor of class, building a {@link JFrame} with menu bar
     */
    public Window(){


        menuBar = new JMenuBar();
        menuBar.setFont(new Font("Times New Roman",Font.PLAIN,30));
        optionsMenu = new JMenu();
        optionsMenu.setFont(new Font("Times New Roman",Font.PLAIN,30));
        signOutButton = new JMenuItem();
        signOutButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        exitButton = new JMenuItem();
        exitButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        modulesMenu = new JMenu();
        modulesMenu.setFont(new Font("Times New Roman",Font.PLAIN,30));
        timetableButton = new JMenuItem();
        timetableButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        attendanceMenu = new JMenu();
        attendanceMenu.setFont(new Font("Times New Roman",Font.PLAIN,30));
        takeAttendanceButton = new JMenuItem();
        takeAttendanceButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        viewAttendanceButton = new JMenuItem();
        viewAttendanceButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        myStudentsButton = new JMenuItem();
        myStudentsButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        myTeachersButton = new JMenuItem();
        myTeachersButton.setFont(new Font("Times New Roman",Font.PLAIN,30));
        profileButton = new JMenuItem();
        profileButton.setFont(new Font("Times New Roman",Font.PLAIN,30));

        setTitle("Apograf");
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        setIconImage(image);
        setBounds(0,0,(int)screenSize.getWidth()*7/8,(int)screenSize.getHeight());
        setMinimumSize(new Dimension(1064,768));


        addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e){
                int i=JOptionPane.showConfirmDialog(null, "Are you sure you want to exit?");
                if(i==0)
                    System.exit(0);
            }
        });
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);




        optionsMenu.setText("Options");


        signOutButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_W, java.awt.event.InputEvent.CTRL_MASK));
        signOutButton.setText("Sign out");
        optionsMenu.add(signOutButton);

        exitButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_Q, java.awt.event.InputEvent.CTRL_MASK));
        exitButton.setText("Exit program");
        optionsMenu.add(exitButton);


        profileButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_D, java.awt.event.InputEvent.CTRL_MASK));
        profileButton.setText("View my profile");
        optionsMenu.add(profileButton);


        menuBar.add(optionsMenu);

        modulesMenu.setText("Modules");


        timetableButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_I, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        timetableButton.setText("My Timetable");
        modulesMenu.add(timetableButton);

        attendanceMenu.setText("Attendance");

        takeAttendanceButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_A, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        takeAttendanceButton.setText("Take attendance");
        attendanceMenu.add(takeAttendanceButton);

        viewAttendanceButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_V, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        viewAttendanceButton.setText("View/change attendance");
        attendanceMenu.add(viewAttendanceButton);
        modulesMenu.add(attendanceMenu);

        myStudentsButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        myStudentsButton.setText("My Students");
        modulesMenu.add(myStudentsButton);

        myTeachersButton.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_T, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        myTeachersButton.setText("My Teachers");
        modulesMenu.add(myTeachersButton);

        menuBar.add(modulesMenu);

        setJMenuBar(menuBar);



        buttonArray= new JMenuItem[]{exitButton, myStudentsButton,
                myTeachersButton, signOutButton,
                takeAttendanceButton, timetableButton, viewAttendanceButton, profileButton};
        buttonArraySize = buttonArray.length;
    }



}
