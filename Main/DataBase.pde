public class FestDatabase {
  final String dbTable, genstandeCol, idCol, nameCol;
  final MySQL database;

  public FestDatabase(MySQL database, String dbTable, String genstandeCol, String idCol, String nameCol) {
    this.dbTable = dbTable;
    this.genstandeCol = genstandeCol;
    this.idCol = idCol;
    this.nameCol = nameCol;
    this.database = database;

    if (!Database.checkTable(database, dbName, dbTable)) {
      println("Table not found");
      return;
    }

    println("The table was successfully found");
  }

  public void addGenstande(int id, int amount) {
    int current = this.getGenstande(id);
    int newAmount = current+amount;
    println(String.format("Ændrer genstande fra %s til nu at være %s", current, newAmount));
    if (Database.rowExists(database, dbTable, id)) {
      database.query(String.format("UPDATE %s SET %s=%s WHERE CardID = %s", this.dbTable, this.genstandeCol, newAmount, id));
    } else {
      println("ERROR: THIS MOTHERFUCKER DOES NOT EXIST");
    }
  }

  public int getGenstande(int id) {
    if (!Database.rowExists(database, this.dbTable, id)) {
      println("ERROR: THIS MOTHERFUCKER DOES NOT EXIST OG HAR IKKE NOGLE FUCKING GENSTANDE");
      return 0;
    }

    Database.select(database, dbTable, genstandeCol, idCol+"="+id);
    database.next();
    return database.getInt(genstandeCol);
  }

  public String getUserName(int id) {
    if (!Database.rowExists(database, this.dbTable, id)) {
      println("ERROR: THIS MOTHERFUCKER DOES NOT EXIST OG HAR IKKE NOGET FUCKING NAVN");
      return "";
    }
      
    Database.select(database, dbTable, nameCol, idCol+"="+id);
    database.next();
    return database.getString(nameCol);
  }
}

public static class Database {

  static boolean checkTable(MySQL database, String dbName, String table) {
    database.query(String.format("SELECT EXISTS ( SELECT * FROM information_schema.tables WHERE table_schema = '%s' AND table_name = '%s' )", dbName, table));
    database.next();
    return boolean(database.getInt(1));
  }

  static boolean rowExists(MySQL database, String table, int id) {
    Database.select(database, table, "COUNT(1)", "CardID="+id);
    database.next();
    return boolean(database.getInt(1));
  }

  private static void select(MySQL database, String table, String selector, String condition) {
    database.query(String.format("SELECT %s FROM %s WHERE %s", selector, table, condition));
  }
}

MySQL connect(String dbHost, int dbPort, String dbName, String dbUser, String dbPass) {
  MySQL mysql = new MySQL(this, dbHost+":"+dbPort, dbName, dbUser, dbPass);
  if (mysql.connect()) {
    println("Successfully connected to the database");
    return mysql;
  } else {
    throw new NullPointerException("Error on connecting to the database");
  }
}
