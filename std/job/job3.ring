//
// File:    job3.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-18
//

package job

import {
}

function std_job3_test1() {

}

function std_job3_test2() {
	
}

typedef class Job3 {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Fmt(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};