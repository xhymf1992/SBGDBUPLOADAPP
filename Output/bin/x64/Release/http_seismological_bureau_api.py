# All rights reserved.
# file name: http_seismological_bureau_api.py
# author: hejunqiang
# date: 2020.06.17
# description: http api for Seismological Bureau with TE

#coding = utf-8


import urllib.request
import urllib.parse
import urllib.error
import json
import ssl


def common_fun(url, data):
    headers = {'content-type': 'application/json'}
    context = ssl._create_unverified_context()

    req = urllib.request.Request(url = url[0], headers=headers, data=json.dumps(data).encode(), method='POST')
    try:
        with urllib.request.urlopen(req, context=context) as response:
            res = response.read()
            json_data = json.loads(res, encoding='utf-8')
            return json_data
            
    except urllib.error.URLError as e:
        return e


def api_add_collected_epimechanismresult(url, sid, points, ids, occurrencedates, occurrencetimes, locationnames, lons, lats, magnitudes, units, depths, shazimuths, stressregimes, \
    plane1strikes, plane1dips, plane1slips, plane2strikes, plane2dips, plane2slips, pazimuths, pplunges, tazimuths, tplunges, bazimuths, bplunges, methods, references, commentinfos):
    data = {'sid':sid, 'points':points, 'ids':ids, 'occurrencedates':occurrencedates, 'occurrencetimes':occurrencetimes, 'locationnames':locationnames, 'lons':lons, 'lats':lats, \
         'magnitudes':magnitudes, 'units':units, 'depths':depths, 'shazimuths':shazimuths, 'stressregimes':stressregimes, 'plane1strikes':plane1strikes, 'plane1dips':plane1dips, \
             'plane1slips':plane1slips, 'plane2strikes':plane2strikes, 'plane2dips':plane2dips, 'plane2slips':plane2slips, 'pazimuths':pazimuths, 'pplunges':pplunges, \
                 'tazimuths':tazimuths, 'tplunges':tplunges, 'bazimuths':bazimuths, 'bplunges':bplunges, 'methods':methods, 'references':references, 'commentinfos':commentinfos}
    return(common_fun(url, data))

