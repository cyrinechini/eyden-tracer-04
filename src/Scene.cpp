#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 1, 1),
            "/Users/cyrinechini/Documents/GitHub/eyden-tracer-04/data/cb.bmp");
		std::vector<Vec3f> vVertexes;
        std::vector<Vec3f> vNormal;
        std::vector<Vec2f> vTextures;
		std::string line, s;
		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
            if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				//std::cout << "Vertex: " << v << std::endl;
				vVertexes.emplace_back(v);
    
			}
            else if (line == "vn") {
                Vec3f n;
                for (int i = 0; i < 3; i++) ss >> n.val[i];
              //  std::cout << "Normal: " << n << std::endl;
                vNormal.emplace_back(n);
            }
            else if (line == "vt") {
                Vec2f t;
                ss >> t.val[0];
                ss >> t.val[1];
                vTextures.emplace_back(t);
            }
			else if (line == "f") {
				Vec3i f;
                Vec3i n;
                Vec3i t;
                for (int i = 0; i < 3; i++) {
                    ss >> s;
                    std::replace(s.begin(), s.end(), '/', ' ');
                    std::stringstream iss(s);
                    iss >> f.val[i];
                    iss >> t.val[i];
                    iss >> n.val[i];
                }
				Add(std::make_shared<CPrimTriangleSmoothTextured>
                    (vVertexes[f.val[0] - 1], vVertexes[f.val[1] - 1], vVertexes[f.val[2] - 1],
                     vNormal[n.val[0] - 1],vNormal[n.val[1] - 1], vNormal[n.val[2] - 1],
                     vTextures[t.val[0] - 1], vTextures[t.val[1] - 1], vTextures[t.val[2] - 1],
                     pShader));
			}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
