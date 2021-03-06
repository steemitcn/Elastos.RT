//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_SECURITY_CERT_CPKIXCERTPATHBUILDERRESULT_H__
#define __ELASTOS_SECURITY_CERT_CPKIXCERTPATHBUILDERRESULT_H__

#include "_Elastos_Security_Cert_CPKIXCertPathBuilderResult.h"
#include "PKIXCertPathValidatorResult.h"

using Elastos::Security::IPublicKey;

namespace Elastos {
namespace Security {
namespace Cert {

CarClass(CPKIXCertPathBuilderResult)
    , public PKIXCertPathValidatorResult
    , public IPKIXCertPathBuilderResult
    , public ICertPathBuilderResult
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CARAPI ToString(
        /* [out] */ String * pStr);

    CARAPI GetCertPath(
        /* [out] */ ICertPath **certPath);

    CARAPI constructor(
        /* [in] */ ICertPath *certPath,
        /* [in] */ ITrustAnchor *trustAnchor,
        /* [in] */ IPolicyNode *policyTree,
        /* [in] */ IPublicKey *subjectPublicKey);

private:
    // Built and validated certification path
    AutoPtr<ICertPath> mCertPath;
};

}
}
}

#endif // __ELASTOS_SECURITY_CERT_CPKIXCERTPATHBUILDERRESULT_H__
