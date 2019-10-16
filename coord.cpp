#include "coord.hpp"

namespace coord{
	#define COORDRET(X) if(((unsigned int)(X))>=(sizeof(cd)/sizeof(cd[0]))){return ENDCOORD;}else{return cd[(X)];}
	pointc otsk(int t){
		static const pointc cd[]={
			{605,1811},{607,1811},{608,1812},{610,1812},{611,1812},{613,1813},{614,1813},{616,1814},{618,1814},{620,1814},{621,1815},{623,1815},{625,1816},{627,1816},{630,1817},{632,1817},{634,1818},{636,1818},{639,1819},{641,1819},{644,1820},{646,1821},{649,1821},{652,1822},{655,1823},{657,1823},{660,1824},{664,1825},{667,1825},{670,1826},{674,1827},{677,1828},{681,1828},{684,1829},{688,1830},{692,1831},{696,1832},{700,1832},{705,1833},{709,1834},{714,1835},{718,1836},{723,1837},{728,1838},{733,1839},{739,1840},{744,1841},{750,1842},{755,1843},{761,1844},{767,1845},{774,1846},{780,1847},{787,1848},{794,1849},{801,1850},{808,1851},{815,1852},{823,1853},{831,1855},{839,1856},{847,1857},{855,1858},{864,1859},{873,1860},{882,1861},{891,1862},{901,1863},{911,1864},{921,1865},{931,1865},{942,1866},{953,1867},{964,1868},{975,1868},{987,1869},{999,1869},{1011,1870},{1024,1870},{1037,1870},{1050,1870},{1063,1870},{1077,1870},{1091,1870},{1105,1870},{1119,1869},{1134,1868},{1149,1867},{1164,1866},{1179,1865},{1195,1863},{1211,1861},{1227,1859},{1244,1857},{1260,1855},{1277,1852},{1294,1849},{1311,1845},{1328,1841},{1346,1837},{1363,1833},{1381,1828},{1399,1822},{1417,1817},{1435,1811},{1452,1804},{1470,1797},{1488,1790},{1506,1782},{1523,1773},{1541,1765},{1558,1755},{1576,1746},{1593,1735},{1610,1725},{1626,1713},{1642,1702},{1658,1690},{1674,1677},{1689,1664},{1704,1650},{1719,1637},{1733,1622},{1746,1607},{1760,1592},{1772,1577},{1785,1561},{1796,1545},{1807,1529},{1818,1512},{1828,1495},{1838,1478},{1847,1461},{1855,1444},{1864,1426},{1871,1408},{1878,1391},{1884,1373},{1890,1355},{1896,1338},{1901,1320},{1905,1302},{1910,1285},{1913,1267},{1916,1250},{1919,1233},{1922,1216},{1924,1199},{1926,1183},{1927,1166},{1928,1150},{1929,1134},{1930,1118},{1930,1103},{1930,1088},{1930,1073},{1929,1058},{1929,1044},{1928,1030},{1927,1016},{1926,1003},{1924,990},{1923,977},{1922,964},{1920,952},{1918,940},{1917,928},{1915,917},{1913,906},{1911,895},{1909,884},{1907,874},{1905,864},{1903,854},{1900,845},{1898,835},{1896,826},{1894,818},{1892,809},{1890,801},{1887,793},{1885,785},{1883,778},{1881,770},{1879,763},{1877,756},{1875,749},{1873,743},{1871,736},{1869,730},{1867,724},{1865,718},{1863,713},{1861,707},{1859,702},{1858,697},{1856,692},{1854,687},{1853,682},{1851,678},{1849,673},{1848,669},{1846,665},{1845,661},{1843,657},{1842,653},{1840,650},{1839,646},{1838,643},{1836,639},{1835,636},{1834,633},{1833,630},{1831,627},{1830,624},{1829,621},{1828,619},{1827,616},{1826,613},{1825,611},{1824,609},{1823,606},{1822,604},{1821,602},{1820,600},{1819,598},{1818,596},{1818,594},{1817,592},{1816,590},{1815,589},{1815,587},{1814,585},{1813,584},{1813,582},{1812,581},{1811,579},{1811,578},{1810,577},{1810,575},{1809,574},{1808,573},{1808,572},{1807,571},{1807,570},{1808,571},{1808,572},{1809,573},{1809,574},{1810,576},{1810,577},{1811,578},{1811,580},{1812,581},{1813,582},{1813,584},{1814,585},{1815,587},{1815,589},{1816,590},{1817,592},{1818,594},{1818,596},{1819,597},{1820,599},{1821,601},{1822,603},{1823,606},{1823,608},{1824,610},{1825,612},{1826,615},{1827,617},{1828,620},{1830,622},{1831,625},{1832,628},{1833,631},{1834,634},{1835,637},{1837,640},{1838,643},{1839,647},{1840,650},{1842,654},{1843,657},{1845,661},{1846,665},{1848,669},{1849,673},{1851,677},{1852,682},{1854,686},{1856,691},{1857,696},{1859,701},{1861,706},{1863,711},{1864,717},{1866,722},{1868,728},{1870,734},{1872,740},{1874,746},{1876,753},{1878,759},{1880,766},{1882,773},{1884,780},{1886,788},{1888,795},{1890,803},{1892,811},{1894,820},{1897,828},{1899,837},{1901,846},{1903,855},{1905,865},{1907,875},{1909,885},{1911,895},{1913,905},{1915,916},{1916,927},{1918,939},{1920,950},{1921,962},{1923,974},{1924,987},{1925,1000},{1927,1013},{1928,1026},{1928,1039},{1929,1053},{1929,1068},{1930,1082},{1930,1097},{1930,1112},{1929,1127},{1929,1142},{1928,1158},{1926,1174},{1925,1190},{1923,1206},{1921,1223},{1918,1240},{1915,1256},{1912,1273},{1908,1291},{1904,1308},{1899,1325},{1894,1343},{1889,1360},{1883,1378},{1876,1395},{1869,1413},{1862,1430},{1854,1447},{1845,1464},{1836,1482},{1826,1498},{1816,1515},{1805,1532},{1794,1548},{1782,1564},{1770,1580},{1757,1595},{1744,1610},{1730,1625},{1716,1639},{1702,1653},{1687,1666},{1671,1679},{1655,1692},{1639,1704},{1623,1716},{1606,1727},{1589,1738},{1572,1748},{1554,1758},{1536,1767},{1519,1776},{1501,1784},{1483,1792},{1464,1799},{1446,1806},{1428,1813},{1410,1819},{1392,1824},{1374,1830},{1356,1835},{1338,1839},{1320,1843},{1303,1847},{1285,1850},{1268,1853},{1251,1856},{1234,1859},{1217,1861},{1201,1863},{1185,1864},{1169,1866},{1153,1867},{1138,1868},{1122,1869},{1108,1869},{1093,1870},{1079,1870},{1065,1870},{1051,1870},{1037,1870},{1024,1870},{1011,1870},{999,1869},{986,1869},{974,1868},{963,1868},{951,1867},{940,1866},{929,1865},{919,1864},{908,1863},{898,1863},{888,1862},{879,1860},{869,1859},{860,1858},{851,1857},{843,1856},{834,1855},{826,1854},{818,1853},{811,1852},{803,1851},{796,1850},{789,1848},{782,1847},{775,1846},{769,1845},{762,1844},{756,1843},{750,1842},{745,1841},{739,1840},{733,1839},{728,1838},{723,1837},{718,1836},{713,1835},{708,1834},{704,1833},{700,1832},{695,1831},{691,1830},{687,1830},{683,1829},{679,1828},{676,1827},{672,1826},{669,1826},{665,1825},{662,1824},{659,1824},{656,1823},{653,1822},{650,1822},{647,1821},{644,1820},{642,1820},{639,1819},{637,1818},{634,1818},{632,1817},{630,1817},{628,1816},{625,1816},{623,1815},{621,1815},{620,1814},{618,1814},{616,1813},{614,1813},{612,1813},{611,1812},{609,1812},{608,1811},{606,1811},
		};
		COORDRET(t/50);
	}
	pointc walkerGo(int t){
		static const pointc cd[]={
			{0,0},{2,0},{2,1},{3,3},{4,5},{4,7},{5,9},{6,11},{7,14},{8,16},{8,19},{9,21},{10,24},{11,27},{12,29},{13,32},{14,35},{15,38},{17,41},{18,45},{19,48},{20,51},{21,55},{23,59},{24,62},{25,66},{27,70},{28,75},{30,79},{31,83},{33,88},{35,92},{36,97},{38,102},{40,107},{42,113},{44,118},{45,124},{48,130},{50,136},{52,142},{54,148},{56,155},{59,161},{61,168},{64,175},{66,183},{69,190},{71,198},{74,206},{77,215},{80,223},{83,232},{86,241},{90,250},{93,260},{96,270},{100,280},{103,291},{107,301},{111,313},{115,324},{119,336},{123,348},{128,361},{132,374},{137,387},{141,401},{146,415},{151,429},{156,444},{161,459},{167,475},{172,491},{178,508},{184,525},{189,543},{196,561},{202,580},{208,599},{215,619},{222,639},{229,660},{236,681},{243,703},{250,726},{258,749},{266,773},{274,798},{282,823},{291,849},{299,875},{308,902},{317,930},{326,959},{336,988},{345,1018},{355,1049},{365,1080},{375,1113},{385,1146},{396,1180},{407,1214},{418,1250},{429,1286},{440,1323},{452,1361},{463,1400},{475,1439},{487,1479},{499,1520},{512,1562},{524,1605},{537,1649},{549,1693},{562,1738},{575,1784},{588,1830},{601,1878},{614,1926},{627,1974},{641,2024},{654,2074},{667,2124},{680,2175},{693,2227},{706,2279},{719,2332},{732,2385},{745,2439},{757,2492},{769,2547},{781,2601},{793,2655},{805,2710},{816,2765},{827,2819},{838,2874},{848,2928},{858,2983},{868,3037},{877,3090},{885,3144},{894,3197},{901,3249},{909,3301},{916,3352},{922,3403},{928,3453},{933,3502},{938,3551},{942,3598},{946,3645},{949,3690},{951,3735},{954,3779},{955,3822},{956,3863},{957,3904},{957,3943},{957,3982},{956,4019},{955,4056},{954,4091},{952,4125},{949,4158},{947,4190},{944,4221},{940,4251},{937,4280},{933,4308},{929,4334},{925,4360},{920,4385},{916,4409},{911,4432},{906,4455},{901,4476},{895,4496},{890,4516},{885,4535},{879,4553},{874,4571},{868,4588},{863,4604},{857,4619},{851,4634},{846,4649},{840,4662},{835,4675},{829,4688},{824,4700},{818,4712},{813,4723},{808,4733},{802,4744},{797,4754},{792,4763},{787,4772},{782,4781},{777,4789},{773,4797},{768,4805},{763,4812},{759,4819},{754,4826},{750,4833},{746,4839},{741,4845},{737,4851},{733,4856},{730,4862},{726,4867},{722,4872},{718,4877},{715,4881},{711,4886},{708,4890},{705,4894},{702,4898},{698,4902},{695,4905},{692,4909},{690,4912},{687,4915},{684,4919},{681,4922},{679,4924},{676,4927},{674,4930},{671,4933},{669,4935},{667,4938},{665,4940},{662,4942},{660,4944},{658,4946},{656,4948},{655,4950},{653,4952},{651,4954},{649,4956},{647,4957},{646,4959},{644,4961},{643,4962},{641,4964},{640,4965},{638,4966},{637,4968},{636,4969},{634,4970},{633,4971},{632,4973},{631,4974},{630,4975},{628,4976},{627,4977},{626,4978},{625,4979},{624,4980},{623,4980},{622,4981},{622,4982},{621,4983},{620,4984},{619,4984},{618,4985},{617,4986},{617,4986},{616,4987},{615,4988},{615,4988},{614,4989},{613,4989},{613,4990},{612,4990},{611,4991},{611,4991},{610,4992},{610,4992},{609,4993},{609,4993},{608,4994},{608,4994},{607,4995},{607,4995},{607,4995},{606,4996},{606,4996},{605,4996},{605,4997},{605,4997},{604,4997},{604,4998},{604,4998},
		};
		COORDRET(t/50);
	}
	pointc walkerBack(int t){
		static const pointc cd[]={
			{563,4898},{563,4897},{563,4897},{562,4897},{562,4896},{562,4896},{561,4895},{561,4895},{560,4895},{560,4894},{560,4894},{559,4893},{559,4893},{558,4892},{558,4892},{558,4891},{557,4891},{557,4890},{556,4890},{556,4889},{555,4888},{554,4888},{554,4887},{553,4886},{553,4886},{552,4885},{551,4884},{551,4884},{550,4883},{549,4882},{549,4881},{548,4880},{547,4879},{547,4878},{546,4877},{545,4876},{544,4875},{543,4874},{542,4873},{541,4872},{540,4871},{540,4869},{539,4868},{538,4867},{537,4865},{535,4864},{534,4863},{533,4861},{532,4859},{531,4858},{530,4856},{528,4854},{527,4852},{526,4851},{525,4849},{523,4847},{522,4844},{520,4842},{519,4840},{517,4838},{516,4835},{514,4833},{513,4830},{511,4827},{509,4825},{508,4822},{506,4819},{504,4815},{502,4812},{500,4809},{499,4805},{497,4801},{495,4798},{493,4794},{491,4790},{489,4785},{487,4781},{484,4776},{482,4771},{480,4766},{478,4761},{476,4756},{473,4750},{471,4744},{469,4738},{466,4732},{464,4725},{462,4718},{459,4711},{457,4703},{454,4696},{452,4688},{450,4679},{447,4670},{445,4661},{443,4652},{440,4642},{438,4632},{435,4621},{433,4610},{431,4598},{429,4586},{427,4573},{425,4560},{422,4546},{421,4532},{419,4517},{417,4501},{415,4485},{414,4468},{412,4451},{411,4433},{409,4414},{408,4394},{407,4374},{406,4352},{406,4330},{405,4307},{405,4283},{405,4259},{405,4233},{405,4206},{405,4179},{406,4150},{407,4120},{408,4089},{409,4058},{410,4025},{412,3991},{413,3956},{415,3920},{418,3883},{420,3844},{422,3805},{425,3764},{428,3723},{431,3680},{434,3636},{437,3591},{440,3546},{444,3499},{447,3451},{450,3402},{454,3353},{457,3302},{461,3251},{464,3199},{467,3146},{470,3093},{473,3039},{475,2985},{478,2930},{480,2875},{482,2820},{484,2764},{485,2708},{486,2652},{487,2596},{488,2540},{488,2485},{488,2429},{487,2374},{486,2318},{485,2264},{483,2209},{481,2156},{479,2102},{476,2050},{473,1997},{470,1946},{466,1895},{462,1845},{458,1796},{453,1747},{448,1700},{443,1653},{438,1607},{432,1562},{426,1518},{420,1474},{414,1432},{408,1391},{401,1350},{394,1310},{388,1271},{381,1234},{374,1197},{367,1161},{360,1125},{353,1091},{346,1058},{338,1025},{331,993},{324,963},{317,933},{310,903},{303,875},{296,847},{289,820},{282,794},{275,769},{268,744},{261,720},{254,697},{248,674},{241,652},{235,631},{229,610},{222,590},{216,571},{210,552},{204,533},{199,515},{193,498},{187,481},{182,465},{177,449},{171,434},{166,419},{161,405},{156,391},{151,377},{147,364},{142,352},{138,339},{133,327},{129,316},{125,304},{121,294},{117,283},{113,273},{109,263},{105,253},{102,244},{98,235},{95,226},{91,218},{88,210},{85,202},{82,194},{79,187},{76,179},{73,172},{70,166},{68,159},{65,153},{63,147},{60,141},{58,135},{55,129},{53,124},{51,118},{49,113},{47,108},{45,104},{43,99},{41,95},{39,90},{37,86},{36,82},{34,78},{32,74},{31,70},{29,67},{28,63},{26,60},{25,57},{23,54},{22,50},{21,47},{19,45},{18,42},{17,39},{16,37},{15,34},{14,32},{13,29},{12,27},{11,25},{10,22},{9,20},{8,18},{7,16},{6,15},{5,13},{5,11},{4,9},{3,8},{2,6},{2,4},{1,3},{0,1},{0,0},
		};
		COORDRET(t/50);
	}
	/*pointc towel1ByHomew(int t){
		static const pointc cd[]={//1
			{604,1801},{604,1803},{604,1806},{604,1808},{604,1811},{604,1814},{604,1817},{604,1820},{604,1824},{604,1828},{604,1832},{604,1837},{604,1842},{604,1847},{604,1853},{604,1859},{604,1866},{604,1873},{604,1881},{604,1889},{604,1898},{604,1908},{604,1919},{604,1930},{604,1942},{604,1955},{604,1970},{604,1985},{604,2002},{604,2019},{604,2039},{604,2059},{604,2082},{604,2106},{604,2131},{604,2159},{604,2189},{604,2221},{604,2256},{604,2293},{604,2333},{604,2376},{604,2422},{604,2471},{604,2524},{604,2580},{604,2641},{604,2705},{604,2773},{604,2845},{604,2921},{604,3002},{604,3087},{604,3176},{604,3269},{604,3366},{604,3466},{604,3569},{605,3674},{605,3782},{605,3891},{605,4001},{605,4111},{605,4220},{605,4330},{605,4414},
		};
		COORDRET(t/80);
	}
	pointc towel1(int t){
		static const pointc cd[]={//1
			{607,4473},{612,4530},{621,4584},{632,4636},{646,4686},{663,4733},{683,4779},{705,4822},{729,4864},{755,4904},{784,4942},{814,4978},{847,5013},{881,5047},{917,5079},{954,5110},{993,5140},{1033,5169},{1074,5197},{1116,5224},{1160,5251},{1204,5276},{1249,5301},{1294,5326},{1340,5351},{1387,5375},{1433,5399},{1480,5423},{1527,5447},{1574,5471},{1621,5495},{1667,5520},{1713,5545},{1758,5570},{1803,5596},{1847,5623},{1890,5651},{1933,5679},{1973,5709},{2013,5739},{2050,5770},{2086,5801},{2119,5832},{2149,5864},{2177,5895},{2203,5927},{2226,5957},{2247,5988},{2265,6017},{2282,6046},{2297,6073},{2310,6100},{2321,6125},{2331,6150},{2340,6173},{2347,6195},{2354,6216},{2360,6235},{2365,6254},{2369,6271},{2373,6287},{2376,6302},{2379,6317},{2381,6330},{2383,6342},{2385,6354},{2386,6365},{2388,6374},{2389,6384},{2390,6392},{2391,6400},{2391,6408},{2392,6415},{2393,6421},{2393,6427},{2394,6432},{2394,6437},{2394,6442},{2395,6446},{2395,6450},{2395,6454},{2395,6457},{2395,6460},{2396,6463},{2396,6466},{2396,6468},{2396,6471},{2396,6473},{2396,6475},{2396,6477},{2396,6478},{2396,6480},{2396,6481},
		};
		COORDRET(t/100);
	}*/
	
	pointc towel1ByHomew(int t){
		static const pointc cd[]={//1
			{442,1515},{442,1567},{442,1569},{442,1572},{442,1575},{442,1578},{442,1581},{442,1585},{442,1588},{442,1592},{442,1596},{442,1600},{442,1604},{442,1609},{442,1614},{442,1619},{442,1624},{442,1630},{442,1636},{442,1642},{442,1648},{442,1655},{442,1663},{442,1670},{442,1678},{442,1687},{442,1696},{442,1705},{442,1715},{442,1725},{442,1736},{442,1748},{442,1760},{442,1772},{442,1786},{442,1800},{442,1815},{442,1830},{442,1847},{442,1864},{442,1882},{442,1901},{442,1921},{442,1942},{442,1965},{442,1988},{442,2012},{442,2038},{442,2065},{442,2094},{442,2124},{442,2156},{442,2189},{442,2223},{442,2260},{442,2298},{442,2339},{442,2381},{442,2426},{442,2472},{442,2521},{442,2572},{442,2626},{442,2682},{442,2741},{442,2803},{442,2867},{442,2934},{442,3005},{442,3078},{442,3155},{442,3234},{442,3317},{442,3403},
		};
		//442 1565
		COORDRET(t/80);
	}
	pointc towel1(int t){
		static const pointc cd[]={//1
			{442,3493},{442,3586},{442,3682},{442,3781},{442,3883},{442,3989},{442,4097},{442,4209},{442,4323},{441,4389},{443,4435},{447,4481},{455,4526},{465,4569},{479,4612},{495,4653},{514,4693},{535,4732},{559,4769},{585,4805},{614,4840},{645,4874},{677,4906},{712,4938},{748,4969},{786,4999},{825,5028},{866,5057},{908,5084},{952,5112},{996,5139},{1042,5165},{1088,5191},{1136,5217},{1183,5243},{1232,5268},{1281,5294},{1330,5319},{1379,5345},{1428,5370},{1478,5396},{1527,5422},{1575,5448},{1623,5475},{1670,5501},{1716,5528},{1760,5555},{1803,5582},{1844,5609},{1883,5636},{1921,5663},{1956,5690},{1990,5717},{2022,5743},{2052,5770},{2080,5796},{2106,5821},{2130,5847},{2153,5872},{2174,5896},{2193,5920},{2211,5943},{2227,5966},{2242,5988},{2256,6010},{2269,6031},{2281,6051},{2291,6071},{2301,6090},{2310,6109},{2318,6127},{2325,6144},{2332,6160},{2338,6176},{2343,6191},{2348,6206},{2353,6220},{2357,6234},{2361,6247},{2364,6259},{2367,6271},{2370,6282},{2372,6293},{2375,6303},{2377,6313},{2379,6323},{2380,6332},{2382,6340},{2383,6348},{2385,6356},{2386,6364},{2387,6371},{2388,6377},{2388,6384},{2389,6390},{2390,6396},{2391,6401},{2391,6407},{2392,6412},{2392,6416},{2393,6421},{2393,6425},{2393,6429},{2394,6433},{2394,6437},{2394,6440},{2394,6444},{2395,6447},{2395,6450},{2395,6452},{2395,6455},{2395,6458},{2395,6460},{2395,6462},{2396,6465},{2396,6467},{2396,6469},{2396,6471},{2396,6472},{2396,6474},{2396,6476},{2396,6477},{2396,6479},{2396,6480},{2396,6481},
		};
		COORDRET(t/100);
	}
	
	/*pointc towel2(int t){
		static const pointc cd[]={
			{2396,6482},{2397,6482},{2397,6482},{2398,6482},{2398,6482},{2399,6482},{2399,6482},{2400,6482},{2401,6482},{2401,6482},{2402,6482},{2403,6482},{2404,6482},{2405,6482},{2406,6482},{2407,6482},{2409,6482},{2410,6482},{2411,6482},{2413,6482},{2415,6482},{2417,6482},{2419,6482},{2421,6482},{2423,6482},{2426,6482},{2428,6482},{2431,6482},{2434,6482},{2438,6482},{2441,6482},{2445,6482},{2449,6482},{2454,6482},{2459,6482},{2464,6482},{2470,6482},{2476,6482},{2483,6482},{2490,6482},{2497,6482},{2505,6482},{2514,6482},{2523,6482},{2533,6482},{2544,6482},{2555,6482},{2568,6482},{2580,6482},{2594,6482},{2609,6482},{2624,6482},{2640,6482},{2657,6482},{2675,6482},{2693,6482},{2712,6482},{2731,6482},{2751,6482},{2772,6482},{2792,6482},{2813,6482},{2834,6482},{2855,6482},{2876,6482},{2897,6482},{2917,6482},{2938,6482},{2959,6482},{2980,6482},{3001,6482},{3022,6482},{3042,6482},{3063,6482},{3084,6482},{3105,6482},{3126,6482},{3147,6482},{3167,6482},{3188,6482},{3209,6482},{3230,6482},{3251,6482},{3272,6482},{3292,6482},{3313,6482},{3333,6482},{3353,6482},{3372,6482},{3391,6482},{3409,6482},{3426,6482},{3442,6482},{3458,6482},{3473,6482},{3487,6482},{3500,6482},{3512,6482},{3523,6482},{3534,6482},{3544,6482},{3553,6482},{3561,6482},{3569,6482},{3577,6482},{3583,6482},{3590,6482},{3596,6482},{3601,6482},{3606,6482},{3611,6482},{3615,6482},{3619,6482},{3622,6482},{3626,6482},{3629,6482},{3631,6482},{3634,6482},{3636,6482},{3639,6482},{3641,6482},{3643,6482},{3644,6482},{3646,6482},{3647,6482},{3649,6482},{3650,6482},{3651,6482},{3652,6482},{3653,6482},{3654,6482},{3655,6482},{3656,6482},{3656,6482},{3657,6482},{3658,6482},{3658,6482},{3659,6482},{3659,6482},
		};
		COORDRET(t/50);
	}*/
	pointc towel2(int t){
		static const pointc cd[]={
			{2396,6482},{2397,6482},{2397,6482},{2398,6482},{2398,6482},{2399,6482},{2400,6482},{2400,6482},{2401,6482},{2402,6482},{2403,6482},{2404,6482},{2404,6482},{2405,6482},{2406,6482},{2407,6482},{2408,6482},{2410,6482},{2411,6482},{2412,6482},{2413,6482},{2415,6482},{2416,6482},{2418,6482},{2419,6482},{2421,6482},{2423,6482},{2425,6482},{2427,6482},{2429,6482},{2431,6482},{2433,6482},{2436,6482},{2438,6482},{2441,6482},{2444,6482},{2447,6482},{2450,6482},{2453,6482},{2457,6482},{2460,6482},{2464,6482},{2468,6482},{2472,6482},{2477,6482},{2482,6482},{2487,6482},{2492,6482},{2497,6482},{2503,6482},{2509,6482},{2515,6482},{2522,6482},{2529,6482},{2536,6482},{2544,6482},{2552,6481},{2561,6481},{2570,6481},{2579,6481},{2589,6481},{2599,6481},{2610,6481},{2621,6481},{2633,6481},{2645,6481},{2658,6481},{2672,6481},{2686,6481},{2701,6481},{2716,6481},{2732,6481},{2749,6481},{2766,6481},{2784,6481},{2803,6481},{2822,6481},{2842,6481},{2863,6481},{2884,6481},{2906,6481},{2928,6481},{2951,6481},{2974,6481},{2998,6481},{3022,6481},{3047,6481},{3072,6481},{3097,6480},{3122,6480},{3148,6480},{3173,6480},{3199,6480},{3224,6480},{3249,6480},{3274,6480},{3298,6480},{3322,6480},{3346,6480},{3369,6480},{3392,6480},{3414,6480},{3436,6480},{3457,6480},{3477,6480},{3497,6480},{3515,6480},{3534,6480},{3551,6480},{3568,6480},{3584,6480},{3600,6480},{3615,6480},{3629,6480},{3643,6479},{3655,6479},{3668,6479},{3680,6479},{3691,6479},{3702,6479},{3712,6479},{3722,6479},{3731,6479},{3740,6479},{3748,6479},{3756,6479},{3763,6479},{3771,6479},{3777,6479},{3784,6479},{3790,6479},{3796,6479},{3801,6479},{3807,6479},{3812,6479},{3816,6479},{3821,6479},{3825,6479},{3829,6479},{3833,6479},{3836,6479},{3840,6479},{3843,6479},{3846,6479},{3849,6479},{3852,6479},{3854,6479},{3857,6479},{3859,6479},{3861,6479},{3864,6479},{3866,6479},{3867,6479},{3869,6479},{3871,6479},{3873,6479},{3874,6479},{3876,6479},{3877,6479},{3878,6479},{3879,6479},{3881,6479},{3882,6479},{3883,6479},{3884,6479},{3885,6479},{3886,6479},{3886,6479},{3887,6479},{3888,6479},{3889,6479},{3889,6479},{3890,6479},{3891,6479},{3891,6479},{3892,6479},
		};
		COORDRET(t/50);
	}
	/*pointc sheetsReadWall(int t){
		static const pointc cd[]={
			{3663,6482},{3663,6483},{3664,6484},{3664,6485},{3665,6486},{3665,6487},{3666,6489},{3666,6490},{3667,6492},{3668,6494},{3669,6496},{3670,6498},{3671,6500},{3672,6502},{3673,6505},{3674,6508},{3675,6511},{3677,6514},{3678,6518},{3680,6521},{3682,6525},{3683,6530},{3686,6534},{3688,6540},{3690,6545},{3693,6551},{3696,6557},{3699,6564},{3703,6571},{3706,6579},{3710,6588},{3715,6597},{3720,6606},{3725,6617},{3731,6628},{3737,6640},{3744,6653},{3752,6666},{3760,6681},{3769,6697},{3778,6713},{3789,6731},{3800,6750},{3813,6769},{3826,6790},{3841,6812},{3857,6835},{3874,6859},{3892,6884},{3912,6910},{3933,6937},{3955,6964},{3978,6992},{4003,7020},{4029,7048},{4055,7076},{4083,7104},{4111,7132},{4140,7159},{4169,7185},{4198,7210},{4227,7233},{4255,7256},{4283,7277},{4310,7297},{4336,7315},{4362,7332},{4386,7347},{4409,7362},{4431,7375},{4451,7387},{4471,7397},{4489,7407},{4506,7416},{4522,7424},{4537,7431},{4551,7437},{4564,7443},{4576,7448},{4587,7453},{4597,7457},{4606,7461},{4615,7465},{4623,7468},{4631,7471},{4638,7473},{4644,7476},{4650,7478},{4655,7480},{4660,7482},{4665,7483},{4669,7485},{4673,7486},{4677,7487},{4680,7488},{4683,7489},{4686,7490},{4688,7491},{4691,7492},{4693,7493},{4695,7493},{4697,7494},{4699,7494},{4700,7495},{4702,7495},{4703,7496},{4704,7496},{4705,7496},{4706,7497},{4707,7497},
		};
		COORDRET(t/50);
	}*/
	pointc sheetsReadWall(int t){
		static const pointc cd[]={
			{3901,6471},{3900,6472},{3900,6473},{3900,6474},{3900,6475},{3900,6477},{3900,6478},{3900,6479},{3900,6481},{3900,6483},{3900,6484},{3899,6486},{3899,6488},{3899,6490},{3899,6492},{3899,6494},{3899,6496},{3899,6499},{3899,6501},{3899,6504},{3898,6507},{3898,6510},{3898,6513},{3898,6516},{3898,6519},{3898,6523},{3898,6527},{3898,6531},{3898,6535},{3898,6539},{3898,6544},{3898,6548},{3898,6553},{3898,6559},{3899,6564},{3899,6570},{3899,6576},{3900,6583},{3900,6589},{3900,6597},{3901,6604},{3902,6612},{3903,6620},{3904,6628},{3905,6637},{3906,6647},{3907,6656},{3909,6667},{3911,6677},{3913,6688},{3915,6700},{3918,6712},{3921,6724},{3924,6738},{3928,6751},{3932,6765},{3936,6780},{3941,6795},{3947,6810},{3953,6826},{3959,6843},{3966,6860},{3974,6877},{3982,6895},{3991,6913},{4001,6932},{4011,6950},{4022,6969},{4034,6989},{4046,7008},{4059,7027},{4073,7047},{4087,7066},{4102,7085},{4117,7104},{4133,7123},{4149,7142},{4166,7160},{4183,7178},{4200,7195},{4218,7212},{4235,7228},{4253,7243},{4270,7258},{4288,7273},{4305,7286},{4322,7299},{4339,7312},{4355,7324},{4371,7335},{4387,7345},{4402,7355},{4417,7364},{4431,7373},{4445,7381},{4458,7389},{4471,7396},{4483,7403},{4495,7409},{4506,7415},{4517,7421},{4528,7426},{4537,7431},{4547,7435},{4556,7440},{4565,7443},{4573,7447},{4581,7451},{4588,7454},{4595,7457},{4602,7459},{4608,7462},{4614,7464},{4620,7467},{4625,7469},{4631,7471},{4636,7473},{4640,7474},{4645,7476},{4649,7478},{4653,7479},{4657,7480},{4660,7482},{4664,7483},{4667,7484},{4670,7485},{4673,7486},{4676,7487},{4678,7488},{4681,7489},{4683,7489},{4685,7490},{4687,7491},{4689,7491},{4691,7492},{4693,7493},{4695,7493},{4696,7494},{4698,7494},{4699,7494},{4701,7495},{4702,7495},{4703,7496},{4704,7496},{4705,7496},{4706,7497},{4707,7497},
		};
		COORDRET(t/50);
	}
	pointc sheetsExtendPoll(int t){
		static const pointc cd[]={
			{4703,7492},{4701,7492},{4699,7492},{4697,7492},{4695,7492},{4692,7492},{4690,7492},{4687,7492},{4684,7492},{4681,7492},{4678,7492},{4675,7492},{4671,7492},{4668,7492},{4664,7492},{4660,7492},{4656,7492},{4651,7492},{4647,7492},{4642,7492},{4637,7492},{4632,7492},{4626,7492},{4621,7492},{4615,7492},{4608,7492},{4602,7492},{4595,7493},{4588,7493},{4580,7493},{4572,7494},{4564,7494},{4556,7494},{4547,7495},{4538,7495},{4528,7496},{4518,7497},{4508,7498},{4497,7499},{4486,7500},{4474,7501},{4462,7503},{4450,7504},{4437,7506},{4424,7508},{4410,7510},{4396,7513},{4382,7515},{4367,7518},{4352,7522},{4337,7525},{4321,7529},{4305,7534},{4289,7538},{4272,7544},{4255,7549},{4239,7555},{4222,7562},{4205,7569},{4188,7577},{4172,7585},{4155,7594},{4139,7604},{4123,7614},{4108,7624},{4092,7636},{4078,7647},{4064,7660},{4050,7672},{4037,7686},{4025,7699},{4013,7713},{4002,7727},{3992,7742},{3983,7757},{3974,7772},{3966,7787},{3959,7801},{3952,7816},{3946,7831},{3940,7845},{3936,7860},{3931,7873},{3927,7887},{3924,7900},{3921,7913},{3918,7925},{3916,7937},{3914,7949},{3912,7960},{3911,7970},{3909,7980},{3908,7990},{3907,7999},{3906,8007},{3906,8016},{3905,8023},{3905,8031},{3904,8038},{3904,8044},{3903,8051},{3903,8056},{3903,8062},{3903,8067},{3903,8072},{3902,8077},{3902,8081},{3902,8085},{3902,8089},{3902,8093},{3902,8097},{3902,8100},{3902,8103},{3902,8106},{3902,8109},{3902,8111},{3902,8114},{3902,8116},{3902,8118},{3902,8120},{3902,8122},{3902,8124},{3902,8126},{3902,8127},{3902,8129},{3902,8130},{3902,8132},{3902,8133},{3902,8134},{3902,8136},{3902,8137},{3902,8138},{3902,8139},{3902,8140},{3902,8140},{3902,8141},{3902,8142},{3902,8143},{3902,8143},{3902,8144},{3902,8145},{3902,8145},
		};
		COORDRET(t/50);
	}
	pointc sheetsSet(int t){
		static const pointc cd[]={
			{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8144},{3901,8145},{3901,8145},{3901,8145},{3901,8145},{3901,8145},{3901,8145},{3901,8146},{3901,8146},{3901,8146},{3901,8146},{3901,8146},{3901,8147},{3901,8147},{3901,8147},{3901,8148},{3901,8148},{3901,8148},{3901,8148},{3901,8149},{3901,8149},{3901,8150},{3901,8150},{3901,8150},{3901,8151},{3901,8151},{3901,8152},{3901,8152},{3901,8153},{3901,8153},{3901,8154},{3901,8155},{3901,8155},{3901,8156},{3901,8157},{3901,8158},{3901,8158},{3901,8159},{3901,8160},{3901,8161},{3901,8162},{3901,8163},{3901,8164},{3901,8165},{3901,8167},{3901,8168},{3901,8169},{3901,8171},{3901,8172},{3901,8174},{3901,8175},{3901,8177},{3901,8179},{3901,8181},{3901,8183},{3901,8185},{3901,8187},{3901,8189},{3901,8192},{3901,8194},{3901,8197},{3901,8200},{3901,8202},{3901,8205},{3901,8208},{3901,8212},{3901,8215},{3901,8218},{3901,8222},{3901,8225},{3901,8229},{3901,8233},{3901,8237},{3901,8241},{3901,8245},{3901,8250},{3901,8254},{3901,8259},{3901,8263},{3901,8268},{3901,8272},{3901,8277},{3901,8282},{3901,8286},{3901,8291},{3901,8296},{3901,8300},{3901,8305},{3901,8310},{3901,8315},{3901,8319},{3901,8324},{3901,8329},{3901,8333},{3901,8338},{3901,8343},{3901,8347},{3901,8352},{3901,8357},{3901,8361},{3901,8366},{3901,8371},{3901,8375},{3901,8380},{3901,8385},{3901,8389},{3901,8394},{3901,8399},{3901,8403},{3901,8408},{3901,8413},{3901,8417},{3901,8422},{3901,8426},{3901,8431},{3901,8435},{3901,8439},{3901,8443},{3901,8447},{3901,8451},{3901,8455},{3901,8459},{3901,8462},{3901,8466},{3901,8469},{3901,8472},{3901,8475},{3901,8478},{3901,8481},{3901,8484},{3901,8486},{3901,8489},{3901,8491},{3901,8493},{3901,8495},{3901,8497},{3901,8499},{3901,8501},{3901,8503},{3901,8504},{3901,8506},{3901,8507},{3901,8509},{3901,8510},{3901,8512},{3901,8513},{3901,8514},{3901,8515},{3901,8516},{3901,8517},{3901,8518},{3901,8519},{3901,8520},{3901,8520},{3901,8521},{3901,8522},{3901,8523},{3901,8523},{3901,8524},{3901,8524},{3901,8525},{3901,8526},{3901,8526},{3901,8526},{3901,8527},{3901,8527},{3901,8528},{3901,8528},{3901,8528},{3901,8529},{3901,8529},{3901,8529},{3901,8530},{3901,8530},{3901,8530},{3901,8530},{3901,8531},{3901,8531},{3901,8531},{3901,8531},{3901,8532},{3901,8532},{3901,8532},{3901,8532},{3901,8532},{3901,8532},{3901,8532},{3901,8533},{3901,8533},{3901,8533},{3901,8533},{3901,8533},{3901,8533},
		};
		COORDRET(t/50);
	}
	pointc sheetsBom(int t){
		static const pointc cd[]={
			{3899,8536},{3899,8536},{3898,8536},{3898,8536},{3898,8536},{3898,8536},{3897,8536},{3897,8536},{3897,8536},{3896,8536},{3896,8536},{3895,8536},{3895,8536},{3895,8536},{3894,8536},{3894,8536},{3893,8536},{3893,8536},{3892,8536},{3891,8536},{3891,8536},{3890,8536},{3889,8536},{3889,8536},{3888,8536},{3887,8536},{3886,8536},{3885,8536},{3884,8536},{3883,8536},{3882,8536},{3881,8536},{3880,8536},{3879,8536},{3878,8536},{3876,8536},{3875,8536},{3873,8536},{3872,8536},{3870,8536},{3868,8536},{3867,8536},{3865,8536},{3863,8536},{3861,8536},{3858,8536},{3856,8536},{3854,8536},{3851,8536},{3848,8536},{3845,8536},{3842,8536},{3839,8536},{3836,8536},{3832,8536},{3829,8536},{3825,8536},{3821,8536},{3817,8536},{3812,8536},{3807,8536},{3802,8536},{3797,8536},{3792,8536},{3786,8536},{3780,8536},{3774,8535},{3768,8535},{3761,8535},{3754,8535},{3747,8535},{3739,8535},{3731,8535},{3723,8535},{3714,8535},{3706,8535},{3696,8535},{3687,8535},{3677,8535},{3667,8535},{3657,8535},{3646,8535},{3635,8535},{3624,8535},{3613,8535},{3601,8535},{3589,8535},{3577,8535},{3565,8535},{3553,8535},{3541,8535},{3529,8535},{3517,8535},{3505,8535},{3493,8535},{3481,8535},{3468,8535},{3456,8535},{3444,8535},{3432,8535},{3420,8535},{3408,8535},{3396,8535},{3384,8535},{3371,8534},{3359,8534},{3347,8534},{3335,8534},{3323,8534},{3311,8534},{3299,8534},{3287,8534},{3274,8534},{3262,8534},{3250,8534},{3238,8534},{3226,8534},{3214,8534},{3202,8534},{3190,8534},{3177,8534},{3165,8534},{3153,8534},{3141,8534},{3129,8534},{3117,8534},{3105,8534},{3093,8534},{3080,8534},{3068,8534},{3056,8534},{3044,8534},{3032,8534},{3020,8534},{3008,8534},{2996,8534},{2983,8534},{2971,8534},{2959,8533},{2947,8533},{2935,8533},{2923,8533},{2911,8533},{2898,8533},{2886,8533},{2874,8533},{2862,8533},{2850,8533},{2838,8533},{2826,8533},{2814,8533},{2801,8533},{2789,8533},{2777,8533},{2765,8533},{2753,8533},{2741,8533},{2729,8533},{2717,8533},{2705,8533},{2693,8533},{2681,8533},{2670,8533},{2658,8533},{2647,8533},{2636,8533},{2626,8533},{2615,8533},{2605,8533},{2596,8533},{2586,8533},{2577,8533},{2568,8533},{2560,8533},{2552,8532},{2544,8532},{2537,8532},{2529,8532},{2523,8532},{2516,8532},{2510,8532},{2504,8532},{2498,8532},{2493,8532},{2488,8532},{2483,8532},{2478,8532},{2473,8532},{2469,8532},{2465,8532},{2461,8532},{2458,8532},{2454,8532},{2451,8532},{2448,8532},{2445,8532},{2442,8532},{2440,8532},{2437,8532},{2435,8532},{2432,8532},{2430,8532},{2428,8532},{2426,8532},{2424,8532},{2423,8532},{2421,8532},{2419,8532},{2418,8532},{2417,8532},{2415,8532},{2414,8532},{2413,8532},{2412,8532},{2411,8532},{2410,8532},{2409,8532},{2408,8532},{2407,8532},{2406,8532},{2405,8532},{2404,8532},{2404,8532},{2403,8532},{2403,8532},{2402,8532},{2401,8532},{2401,8532},{2400,8532},{2400,8532},{2399,8532},{2399,8532},{2399,8532},{2398,8532},{2398,8532},{2397,8532},{2397,8532},{2397,8532},{2397,8532},{2396,8532},{2396,8532},{2396,8532},
		};
		COORDRET(t/50);
	}
	pointc goback(int t){
		static const pointc cd[]={
			{2403,8541},{2403,8540},{2403,8539},{2403,8538},{2403,8536},{2403,8535},{2403,8534},{2403,8532},{2403,8530},{2403,8529},{2403,8527},{2403,8525},{2403,8523},{2403,8521},{2403,8519},{2403,8517},{2403,8515},{2402,8512},{2402,8510},{2402,8507},{2402,8504},{2402,8501},{2402,8498},{2401,8495},{2401,8491},{2401,8488},{2401,8484},{2400,8480},{2400,8476},{2400,8471},{2399,8467},{2399,8462},{2398,8457},{2398,8452},{2397,8446},{2396,8440},{2395,8434},{2394,8428},{2393,8421},{2392,8414},{2391,8407},{2390,8399},{2388,8391},{2386,8383},{2385,8374},{2382,8365},{2380,8355},{2378,8345},{2375,8335},{2372,8324},{2369,8312},{2365,8300},{2361,8288},{2356,8275},{2351,8262},{2346,8248},{2340,8234},{2333,8219},{2326,8203},{2318,8187},{2309,8170},{2300,8153},{2290,8135},{2278,8117},{2266,8098},{2253,8078},{2238,8058},{2222,8038},{2205,8016},{2186,7995},{2166,7973},{2145,7950},{2121,7927},{2096,7903},{2070,7879},{2041,7855},{2011,7830},{1979,7805},{1945,7779},{1909,7753},{1871,7727},{1832,7701},{1791,7675},{1748,7648},{1704,7622},{1659,7595},{1613,7568},{1566,7540},{1518,7513},{1470,7486},{1422,7458},{1374,7431},{1326,7403},{1279,7375},{1232,7347},{1186,7318},{1140,7289},{1096,7260},{1052,7230},{1010,7200},{969,7168},{930,7136},{892,7103},{855,7070},{821,7035},{788,6999},{757,6962},{728,6924},{702,6885},{678,6844},{656,6802},{638,6759},{621,6714},{608,6667},{598,6619},{590,6569},{586,6517},{586,6469},{586,6428},{586,6388},{587,6347},{587,6307},{587,6266},{588,6225},{588,6185},{588,6144},{589,6103},{589,6063},{589,6022},{590,5981},{590,5941},{591,5900},{591,5860},{591,5819},{592,5778},{592,5738},{592,5697},{593,5656},{593,5616},{593,5575},{594,5534},{594,5494},{594,5453},{595,5413},{595,5372},{595,5331},{596,5291},{596,5250},{596,5209},{597,5169},{597,5128},{597,5087},{598,5047},{598,5006},{598,4966},{599,4925},{599,4884},{599,4844},{600,4803},{600,4762},{600,4722},{601,4681},{601,4640},{601,4600},{602,4559},{602,4519},{603,4478},{603,4437},{603,4397},{604,4356},{604,4315},{604,4275},{605,4234},{605,4193},{605,4153},{606,4112},{606,4071},{606,4031},{607,3990},{607,3950},{607,3909},{608,3868},{608,3828},{608,3787},{609,3746},{609,3706},{609,3665},{610,3624},{610,3584},{610,3543},{611,3503},{611,3462},{611,3421},{612,3381},{612,3340},{612,3299},{613,3259},{613,3218},{613,3177},{614,3137},{614,3096},
		};
		COORDRET(t/50);
	}
	pointc gobackByHomew(int t){
		static const pointc cd[]={
			{615,3056},{615,3015},{615,2974},{616,2934},{616,2893},{616,2853},{617,2813},{617,2774},{617,2735},{618,2697},{618,2660},{618,2623},{618,2588},{619,2553},{619,2520},{619,2487},{620,2455},{620,2425},{620,2395},{620,2367},{621,2340},{621,2314},{621,2289},{621,2265},{621,2242},{622,2220},{622,2199},{622,2179},{622,2160},{622,2141},{622,2124},{623,2108},{623,2092},{623,2077},{623,2063},{623,2049},{623,2036},{623,2024},{623,2013},{623,2002},{623,1991},{624,1981},{624,1972},{624,1963},{624,1954},{624,1946},{624,1939},{624,1932},{624,1925},{624,1918},{624,1912},{624,1906},{624,1901},{624,1895},{624,1890},{624,1886},{624,1881},{624,1877},{624,1873},{625,1869},{625,1866},{625,1862},{625,1859},{625,1856},{625,1853},{625,1850},{625,1848},{625,1845},{625,1843},{625,1841},{625,1838},{625,1836},{625,1835},{625,1833},{625,1831},{625,1829},{625,1828},{625,1827},{625,1825},{625,1824},{625,1823},{625,1821},{625,1820},{625,1819},{625,1818},{625,1817},{625,1816},{625,1816},
		};
		COORDRET(t/50);
	}
};