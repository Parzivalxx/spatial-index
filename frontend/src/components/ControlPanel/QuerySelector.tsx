import React from 'react';

interface QuerySelectorProps {
  selectedDataStructure: string;
  selectedQueryType: string;
  onDataStructureChange: (dataStructure: string) => void;
  onQueryTypeChange: (queryType: string) => void;
  numNearestNeighbours: number;
  onNumNearestNeighboursChange: (num: number) => void;
  queryTime: number;
}

const QuerySelector: React.FC<QuerySelectorProps> = ({
  selectedDataStructure,
  selectedQueryType,
  onDataStructureChange,
  onQueryTypeChange,
  numNearestNeighbours,
  onNumNearestNeighboursChange,
  queryTime,
}) => {
  const isKnnQuery = selectedQueryType === 'knn';
  return (
    <div className="container pb-3">
      <div className="row">
        <div className="col-md-6">
          <label htmlFor="dataStructureSelect">Data Structure:</label>
          <select
            className="form-control"
            id="dataStructureSelect"
            value={selectedDataStructure}
            onChange={(e) => onDataStructureChange(e.target.value)}
          >
            <option value="quadtree">Quad Tree</option>
            <option value="kdtree">KD-Tree</option>
            <option value="bruteforce">Brute Force</option>
          </select>
        </div>
        <div className="col-md-6">
          <label htmlFor="queryTypeSelect">Query Type:</label>
          <select
            className="form-control"
            id="queryTypeSelect"
            value={selectedQueryType}
            onChange={(e) => onQueryTypeChange(e.target.value)}
          >
            <option value="range">Range Query</option>
            <option value="knn">KNN Query</option>
          </select>
        </div>
        {isKnnQuery ? (
          <div className="pt-3">
            <label htmlFor="numNearestNeighbours">Number of Nearest Neighbors:</label>
            <input
              type="number"
              className="form-control"
              id="numNearestNeighbours"
              value={numNearestNeighbours}
              onChange={(e) => onNumNearestNeighboursChange(Number(e.target.value))}
            />
            <p className="mt-3">Click on the chart to perform your knn queries!</p>
          </div>
        ) : (
          <p className="mt-3">Drag and draw rectangles on the chart to perform your range queries!</p>
        )}
        <div className="row mt-4">
          <p className="text-secondary">
            Query time:{' '}
            <span>
              <h1>{queryTime}</h1> ms
            </span>
          </p>
        </div>
      </div>
    </div>
  );
};

export default QuerySelector;
