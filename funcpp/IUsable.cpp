#include"IUsable.h"

std::array<CiblageInfo, 3> IUsable::infoCiblage = {
	CiblageInfo{"MonoCible",new MonoCible},
	CiblageInfo{"MultiCible",new MultiCible},
	CiblageInfo{"SelfCible",new SelfCible}
};