/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkNamespace_h
#define itkNamespace_h

#define ITK_NAMESPACE_IS_NOT_ITK
#define ITK_NAMESPACE itk

#if defined(ITK_NAMESPACE_IS_NOT_ITK) && !defined(itk)
#define itk ITK_NAMESPACE
#endif

#endif //itkNamespace_h
