package aep;

import java.sql.SQLException;
import java.util.List;

public class AppRepository {

	public static void main(String[] args) throws SQLException {
		ConnectionManager connManager = new ConnectionManager();
		try {
			PontoRepository repo = new PontoRepository(connManager);

			Ponto saoJose = new Ponto("São José", "124", "maringa - PR", "Vidro");
			saoJose = repo.save(saoJose);

			Ponto mariaJose = new Ponto("Maria José", "321", "maringa - PR", "Baterias");
			mariaJose = repo.save(mariaJose);
			connManager.commit();

			List<Ponto> pontoRegistrados = repo.findAll();
			System.out.println("Pontos:");
			for (Ponto ponto : pontoRegistrados) {
				System.out.println(ponto.toString());
			}

			for (Ponto ponto : pontoRegistrados) {
				repo.deleteById(ponto.getId());
			}
			connManager.commit();

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			connManager.close();
		}
	}

}
