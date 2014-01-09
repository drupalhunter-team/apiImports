var includes = ['utils/stockUtils.js']

var availibleImports = [ { importName: 'Импорт складских карточек',
                           importFunction: 'runImportDepotcards' },
						 { importName: 'Импорт складских ВЗН',
						   importFunction: 'runImportStockInplants' }
					   ]

var availibleExports = []

var server = 'http://localhost:8080'

function runImportDepotcards()
{
//	var path = utils.chooseFile();
//	var params = { login: 'avs',
//                   password: '123456',
//				   path: path
//				 };
//				 
//	API.call( server + '/login.getAuthToken', params );
//	
//	var fileContent = utils.readFile( path );
//	utils.log( fileContent );
	
	progress.setName1( 'test' );
	progress.setMaximum1( 10 );
	for( var i = 0; i < 10; i++) {
		progress.setValue1( i );

		progress.setName2( i );
		progress.setMaximum2( 100 );
		for( var j = 0; j < 100; j++) {
			utils.sleep(10000)
			progress.setValue2( j );
		}
	}

	utils.log( findStockobjByNomSign( 'asd' ) );
}

function runImportStockInplants() {
	utils.log( 'asd' );
}
