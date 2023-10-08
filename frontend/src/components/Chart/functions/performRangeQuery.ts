import { SetStateAction } from 'react';
import { BASE_URL, ENDPOINTS } from '../../../apiConfig';
import { Point } from '../../../types/Point';

export const performRangeQuery = async (
  selectionRect: {
    startX: number;
    startY: number;
    endX: number;
    endY: number;
  },
  dataStructure: string,
  setQueriedPoints: React.Dispatch<SetStateAction<never[]>>,
  queriedPoints: Point[],
) => {
  const { startX, startY, endX, endY } = selectionRect;
  try {
    const response = await fetch(`${BASE_URL}${ENDPOINTS.RANGE_QUERY}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        startx: startX,
        starty: startY,
        endx: endX,
        endy: endY,
        structure_type: dataStructure,
      }),
    });

    if (!response.ok) {
      throw new Error('Failed to perform range query');
    }

    const data = await response.json();
    const newQueriedPoints = data.points;
    if (!arraysAreEqual(queriedPoints, newQueriedPoints)) {
      setQueriedPoints(newQueriedPoints);
    }
  } catch (error) {
    console.error('Error performing range query:', error);
  }
};

const arraysAreEqual = (arr1: Point[], arr2: Point[]): boolean => {
  const comparePoints = (point1: Point, point2: Point): number => {
    if (point1.x !== point2.x) {
      return point1.x - point2.x;
    }
    return point1.y - point2.y;
  };

  const sortedArr1 = arr1.slice().sort(comparePoints);
  const sortedArr2 = arr2.slice().sort(comparePoints);

  if (sortedArr1.length !== sortedArr2.length) {
    return false;
  }

  for (let i = 0; i < sortedArr1.length; i++) {
    if (sortedArr1[i].x !== sortedArr2[i].x || sortedArr1[i].y !== sortedArr2[i].y) {
      return false;
    }
  }

  return true;
};
