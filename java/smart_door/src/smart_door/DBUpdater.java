package smart_door;

import java.io.BufferedWriter;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Formatter;

import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;


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

	private Connection con = null;
	private Statement stmt = null;
	private int rs = 0;

	@Override
	protected void processEvent(Event ev) {

		StringBuilder sbuf = new StringBuilder();
		Formatter fmt = new Formatter(sbuf);
		Date date = new Date();
		System.out.println("DB --- UpdateTemp");
		

		try {

			String sql = null;
			if (ev instanceof MsgEvent) {
				con = ConnectionManager.getConnection();
				stmt = con.createStatement();
				Msg msg = ((MsgEvent) ev).getMsg();
				
				java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				String currentTime = sdf.format(date);
				System.out.println(currentTime);
				String insertTableSQL = "INSERT INTO dataLogger (valore, tipo, dtm) VALUES "
						+ "(?,?,?)";
				PreparedStatement preparedStatement = con.prepareStatement(insertTableSQL);
				
				int temp = ((UpdateTemp) msg).getT();
				if (msg instanceof UpdateTemp) {
					preparedStatement.setInt(1, temp);
					preparedStatement.setString(2, "T");
					preparedStatement.setTimestamp(3,  new java.sql.Timestamp(date.getTime()));
					preparedStatement .executeUpdate();
					
				} else { 
					if (msg instanceof UpdateInt) {
						
						int lumen = ((UpdateInt) msg).getI();
						//fmt.format("INSERT INTO dataLogger (valore, tipo, dtm) VALUES (%d,%s,%t)",lumen,"I",date);
						//sql = sbuf.toString();
						//rs = stmt.executeUpdate(sql);
					}
				}
				
				con.close();
	
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
