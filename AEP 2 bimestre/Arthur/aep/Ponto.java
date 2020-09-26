package aep;

public class Ponto {
	private Long id;
	private String rua;
	private String numero;
	private String cidade;
	private String item;

	public Ponto(Long id, String rua, String numero, String cidade, String item) {
		this(rua, numero, cidade, item);
		this.id = id;
	}

	public Ponto(String rua, String numero, String cidade, String item) {
		this.rua = rua;
		this.numero = numero;
		this.cidade = cidade;
		this.item = item;
	}

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getRua() {
		return rua;
	}

	public void setRua(String rua) {
		this.rua = rua;
	}

	public String getNumero() {
		return numero;
	}

	public void setNumero(String numero) {
		this.numero = numero;
	}

	public String getCidade() {
		return cidade;
	}

	public void setCidade(String cidade) {
		this.cidade = cidade;
	}

	public String getItem() {
		return item;
	}

	public void setItem(String item) {
		this.item = item;
	}

	@Override
	public String toString() {
		return " id:" + id + ", rua:" + rua + ", numero:" + numero + ", cidade:" + cidade + ", item:" + item;
	}

}
