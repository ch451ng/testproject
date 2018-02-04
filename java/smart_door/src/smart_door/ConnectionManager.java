package smart_door;

import java.sql.*;

public class ConnectionManager {
    private static String url = "jdbc:mysql://192.168.0.8:3306/seiot";    
    private static String driverName = "com.mysql.jdbc.Driver";   
    private static String username = "seiotuser";   
    private static String password = "raspberry";
    private static Connection con;
    private static String urlstring;

    public static Connection getConnection() {
        try {
            Class.forName(driverName);
            try {
                con = DriverManager.getConnection(url, username, password);
            } catch (SQLException ex) {
                // log an exception. for example:
                System.out.println("Failed to create the database connection."); 
            }
        } catch (ClassNotFoundException ex) {
            // log an exception. for example:
            System.out.println("Driver not found."); 
        }
        return con;
    }

}