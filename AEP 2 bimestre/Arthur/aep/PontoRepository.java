package aep;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class PontoRepository {

	private ConnectionManager connectionManager;

	public PontoRepository(ConnectionManager connectionManager) {
		this.connectionManager = connectionManager;
		this.createTable();
	}

	private void createTable() {
		PreparedStatement psCreateTable = null;
		try {
			psCreateTable = connectionManager.prepareStatement("create table if not exists ponto ("
					+ "id long not null primary key," + "rua varchar(255) not null," + "numero varchar(255) not null,"
					+ "cidade varchar(255) not null," + "item varchar(255) not null" + ")");
			psCreateTable.executeLargeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (psCreateTable != null) {
				try {
					psCreateTable.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public Ponto findById(Long id) throws SQLException {
		Ponto found = null;
		PreparedStatement psSelect = connectionManager
				.prepareStatement("select id, rua, numero, cidade, item from ponto where id = ?");
		psSelect.setLong(1, id);
		ResultSet rsSelect = psSelect.executeQuery();
		try {
			if (rsSelect.next()) {
				found = new Ponto(rsSelect.getLong("id"), rsSelect.getString("rua"), rsSelect.getString("numero"),
						rsSelect.getString("cidade"), rsSelect.getString("item"));
			}
		} finally {
			rsSelect.close();
			psSelect.close();
		}
		return found;
	}

	public Ponto save(Ponto Ponto) {
		boolean exists = Ponto.getId() != null;
		PreparedStatement psSave = null;
		try {
			if (exists) {
				psSave = connectionManager.prepareStatement(
						"update ponto set rua = ?, numero = ?,set cidade = ?, set item = ? where id = ?");
				psSave.setString(1, Ponto.getRua());
				psSave.setString(2, Ponto.getNumero());
				psSave.setString(3, Ponto.getCidade());
				psSave.setString(4, Ponto.getItem());
				psSave.setLong(5, Ponto.getId());
			} else {
				Long id = selectNewId();
				
				psSave = connectionManager
						.prepareStatement("insert into ponto (id, rua, numero, cidade, item) values (?,?,?,?,?)");
				psSave.setLong(1, id);
				psSave.setString(2, Ponto.getRua());
				psSave.setString(3, Ponto.getNumero());
				psSave.setString(4, Ponto.getCidade());
				psSave.setString(5, Ponto.getItem());
				Ponto = new Ponto(id, Ponto.getRua(), Ponto.getNumero(), Ponto.getCidade(), Ponto.getItem());
			}
			psSave.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				psSave.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return Ponto;
	}

	private Long selectNewId() throws SQLException {
		PreparedStatement psSelect = connectionManager
				.prepareStatement("select coalesce(max(id),0)+1 as newId from ponto");
		ResultSet rsSelect = psSelect.executeQuery();
		try {
			if (rsSelect.next()) {
				return rsSelect.getLong("newId");
			}
		} finally {
			rsSelect.close();
			psSelect.close();
		}
		return null;
	}

	public void deleteById(Long id) throws SQLException {
		PreparedStatement psDelete = connectionManager.prepareStatement("delete from ponto where id = ?");
		psDelete.setLong(1, id);
		try {
			psDelete.executeUpdate();
		} finally {
			psDelete.close();
		}
	}

	public List<Ponto> findAll() throws SQLException {
		List<Ponto> all = new ArrayList<>();
		PreparedStatement psSelect = connectionManager
				.prepareStatement("select id, rua, numero,cidade, item from ponto");
		ResultSet rsSelect = psSelect.executeQuery();
		try {
			while (rsSelect.next()) {
				Ponto Ponto = new Ponto(rsSelect.getLong("id"), rsSelect.getString("rua"), rsSelect.getString("numero"),
						rsSelect.getString("cidade"), rsSelect.getString("item"));
				all.add(Ponto);
			}
		} finally {
			rsSelect.close();
			psSelect.close();
		}
		return all;
	}

}
