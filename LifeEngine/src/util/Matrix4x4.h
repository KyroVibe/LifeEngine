#pragma once

//namespace LifeEngine {
//
//	struct Column4 {
//	public:
//		Column4(float a, float b, float c, float d) {
//			data[0] = a;
//			data[1] = b;
//			data[2] = c;
//			data[3] = d;
//		}
//		~Column4() {
//			delete data;
//		}
//
//		float& operator[] (int index) {
//			return data[index];
//		}
//	private:
//		(float&)* data = new float&[4]; // ???
//	};
//
//	struct Row4 {
//	public:
//		Row4(float a, float b, float c, float d) {
//			data[0] = a;
//			data[1] = b;
//			data[2] = c;
//			data[3] = d;
//		}
//		~Row4() {
//
//		}
//
//		float& operator[] (int index) {
//
//		}
//	private:
//		float* data = new float[4];
//	};
//
//	/*
//	* M[Column][Row]
//	*/
//	class Matrix4x4 {
//	public:
//		// Matrix4x4();
//		~Matrix4x4() {
//			delete columns;
//		}
//
//		Column4& operator[] (int index) {
//			return columns[index];
//		}
//	private:
//		Column4* columns = new Column4[4];
//	};
//
//}
