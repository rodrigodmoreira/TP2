/****************************************************************************************************************/
									TP2 - Rodrigo Dias, Antonio Diniz
										Prof. Flávio Countinho
									Eng. de Computação - CEFET-MG - 2017/2
/****************************************************************************************************************/

							Link do git: https://github.com/rodrigodmoreira/TP2

/****************************************************************************************************************/

										Bibliotecas: 	-lglut
														-lGLU
														-lGL
														-lGLEW
														-lSOIL
														-lm
														-lopenal
														-lalut

/****************************************************************************************************************/

					Compilação: desta vez, basta um "make run" na pasta principal =D

/****************************************************************************************************************/

												Descrição / Adicionais

	# Mundo
		- Constituído de um prédio e cidade
		- Diversos prédios, postes, árvores e asfalto xD
		- Céu estrelado com geração de constelação "procedural" (nunca será o mesmo céu toda vez que abrir)
		- Avião que dá um rasante pela cidade (inclui leve turbulência)(essa parte é mas psicológica msm)
		- Nuvens que giram ao redor da cidade
		- Sol que rotaciona ao redor da cidade

		^^^^ só aqui já existem objetos que sofrem transformações constantes na cena ao decorrer do tempo
			 mais abaixo existem outros
	
	# C̶a̶s̶i̶n̶h̶a̶	Prédio
		- Lado externo detalhado com janelas... e detalhes arquitetônicos do prédio
		- Parte interna constituída do hall com:
			@ móveis simples - sofá, tapetem balcão, vaso de plantas
			@ 3 atendentes robos que flutuam (efeito animado com transformações)
			@ Elevador "funcional". Pressione --R-- para subir
		- e do apartamento:
			@ Monitores que brilham e mudam de cor
			@ Um bom PS4
			@ Lampada (até o momento não é uma fonte de luz)
			@ Sofás e pufs... e muitas almofadas (mtas msm)
			@ Teclados para... codar... e CAFÉ!!!
			@ Quarto com "SuperPC", cama e teclado para o mesmo (bela vista tbm)
			@ Sala de servidor ao lado.... pq sim!! AESTETHICS!!!!
				(luzes que piscam pra dar um efeito de que tá ligado e rodado algo)
			@ Um elevador com porta animada
			@ E cabos no teto... vários... (AESTETHICS!!!)
			@ Existe varanda, mas programadores/otacus/gamers não ficam na varanda
				e sim em suas bases escuras e sombrias (por isso apenas um elevador =D )

	# Câmera
		- gluPerspective
		- HEAD BOBBING =D / Respiração (se intensifica durante a corrida)
		- Utilização de mouse para guiar a câmera

	# Gráficos
		- Modelo de iluminação configurado (Gourad)
		- Razão de aspecto mantida
		- Skybox - feito 3D, com sol, lua e nuvens modelados 3d, além de estrelas procedurais animadas (piscam e aumentam tamanho)
		- Ciclo dia e noite
		- Fog

	# .obj
		- Carregamento de tudo realizado por um carregador de obj (vlw Nate =P)

	# Colisão
		- Meio roubado, mas há uma colisão mais externa com o mapa e, caso esteja no apartamento,
			existe colisão com as paredes que delimitam a área

	# Otimizações
		- Utilizando display list para melhorar a performance e para atenuar "flickering" durante fullscreen

	# Música
		- Música temática (infelizmente não pôde ser 3D porque percebi que havia alguns detalhes a mais para funcionar corretamente
							e não havia tempo disponível para explorar o openAL)
						(na realidade, por algum motivo, dá certo para sons na origem do mundo, mas ainda é necessário
							uma pesquisa para compreender o comportamento da biblioteca )
			@ Música: Vance Joy - Lay It On Me (Said The Sky Remix)