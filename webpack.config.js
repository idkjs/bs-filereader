const path = require('path');
const outputDir = path.resolve(__dirname, 'test_dist');
const webpack = require('webpack');

const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
  entry: './test/Test.bs.js',
  mode: 'development',
  output: {
    path: outputDir,
    filename: 'test.js',
    publicPath: ''
  },
  plugins: [
    new HtmlWebpackPlugin({
      inject: true
    })
  ]
};
