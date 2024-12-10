//
// File:    time.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-14
//

package strings

import {

}

function join(var string[] a, var string sep) -> (string) {
	var string result;

	var int i = 0;

	for(i = 0; i < len(a); i++) {
		result = result .. a[i];
		if (i != len(a) - 1) {
			result = result .. sep;
		}
	}
	
	return result;
}