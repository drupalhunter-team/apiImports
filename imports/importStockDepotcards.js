var includes = ['utils/stockUtils.js']

var availibleImports = [ { importName: 'Импорт складских карточек',
                           prepareFunction: 'prepareImportDepotcards',
                           importFunction: 'runImportDepotcards' },
						 { importName: 'Импорт складских ВЗН',
						   importFunction: 'runImportStockInplants' }
					   ]

var availibleExports = []

var server = 'http://localhost:8080'

function prepareImportDepotcards()
{
	var sourceFile = utils.chooseFile();
	return { sourceFile: sourceFile };
}

function runImportDepotcards( preparedParams )
{
//	utils.log('123')
//	var sourceFile = utils.chooseFile();

	utils.log( preparedParams['sourceFile'] );

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
