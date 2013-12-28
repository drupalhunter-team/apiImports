var server = 'http://localhost:8080'

function runImport()
{
	var path = UTILS.chooseFile();
	var params = { login: 'avs',
                   password: '123456',
				   path: path
				 };
	API.call( server + '/login.getAuthToken', params );
}
