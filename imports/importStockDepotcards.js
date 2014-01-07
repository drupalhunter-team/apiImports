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

	utils.log( findStockobjByNomSign( 'asd' ) );
}

function runImportStockInplants() {
	utils.log( 'asd' );
}
