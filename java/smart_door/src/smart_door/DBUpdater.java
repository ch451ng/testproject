package smart_door;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;

import java.sql.*;

public class DBUpdater extends ReactiveAgent {

	// JDBC driver name and database URL
	static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
	static final String DB_URL = "jdbc:mysql://localhost/EMP";

	// Database credentials
	static final String USER = "username";
	static final String PASS = "password";

	@Override
	protected void processEvent(Event ev) {
		Connection conn = null;
		Statement stmt = null;

		// STEP 2: Register JDBC driver
		try {
			Class.forName("com.mysql.jdbc.Driver");

			// STEP 3: Open a connection
			System.out.println("Connecting to database...");
			conn = DriverManager.getConnection(DB_URL, USER, PASS);

			// STEP 4: Execute a query
			System.out.println("Creating statement...");
			stmt = conn.createStatement();
			String sql = null;
			if (ev instanceof UpdateTemp) {
				sql = "UPDATE Registration " +
						"SET age = 30 WHERE id in (100, 101)";
			} else { 
				if (ev instanceof UpdateInt) {
					sql = "UPDATE Registration " +
							"SET age = 30 WHERE id in (100, 101)";
				}
			}

			stmt.executeUpdate(sql);


		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
