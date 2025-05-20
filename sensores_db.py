import sqlite3

# Conexão e criação da tabela
conn = sqlite3.connect('sensores.db')
cursor = conn.cursor()
cursor.execute('''
CREATE TABLE IF NOT EXISTS leituras (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    fosforo BOOLEAN,
    potassio BOOLEAN,
    ph REAL,
    umidade REAL,
    bomba BOOLEAN,
    data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
)
''')
conn.commit()

# Funções CRUD
def inserir_leitura(fosforo, potassio, ph, umidade, bomba):
    cursor.execute('''
    INSERT INTO leituras (fosforo, potassio, ph, umidade, bomba)
    VALUES (?, ?, ?, ?, ?)
    ''', (fosforo, potassio, ph, umidade, bomba))
    conn.commit()

def consultar_leituras():
    cursor.execute('SELECT * FROM leituras')
    return cursor.fetchall()

def atualizar_leitura(id, **kwargs):
    campos = ', '.join([f"{k}=?" for k in kwargs])
    valores = list(kwargs.values()) + [id]
    cursor.execute(f'UPDATE leituras SET {campos} WHERE id=?', valores)
    conn.commit()

def remover_leitura(id):
    cursor.execute('DELETE FROM leituras WHERE id=?', (id,))
    conn.commit()

# Exemplo de uso:
if __name__ == "__main__":
    # Inserção simulada (copie os dados do monitor serial)
    inserir_leitura(True, True, 6.5, 35.0, True)
    inserir_leitura(False, True, 7.2, 45.0, False)

    print("Leituras:")
    for row in consultar_leituras():
        print(row)

    # Atualização de exemplo
    atualizar_leitura(1, ph=6.8, umidade=38.0)

    # Remoção de exemplo
    remover_leitura(2)
